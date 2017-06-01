#include "raytracer.h"

RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      const size_t samples,
                      const size_t maximum_depth,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        samples_{ samples},
        maximum_depth_{ maximum_depth },
        buffer_( buffer )
{}

Ray RayTracer::get_new_ray( IntersectionRecord intersection_record )
{
    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float theta = glm::acos( 1 - r1 );
    float phi = 2 * M_PI * r2;
    ONB onb_;

    onb_.setFromV(intersection_record.normal_);

    glm::vec3 cartesian_coordinate{ cosf(phi)*sinf(theta), cosf(theta), sinf(phi)*sinf(theta) };

    return Ray{ intersection_record.position_ + (intersection_record.normal_*0.001f), onb_.getBasisMatrix() * cartesian_coordinate };
}


Ray RayTracer::get_reflection(IntersectionRecord intersection_record, Ray ray)
{
    ONB onb_;

    onb_.setFromV(intersection_record.normal_);

    Ray newray;

    glm::vec3 newdir = glm::transpose(onb_.getBasisMatrix()) * ray.direction_;
    newdir = { newdir.x, -newdir.y, newdir.z };
    newray = { intersection_record.position_ + (intersection_record.normal_*0.001f), onb_.getBasisMatrix() * newdir };

    return newray;
}


float RayTracer::rSchlick2(glm::vec3 incident, glm::vec3 normal, float n1, float n2){

    float Ro = (n1 - n2)/(n1 + n2);
    Ro *= Ro;
    float cosX = -glm::dot(normal, incident);
    //cosX = cosX < 0.0f? -cosX : cosX;
    if(n1 > n2){
        float n = n1 / n2;
        float cosT2 = 1.0f - n * n * (1.0f - cosX * cosX);
        if(cosT2 < 0.0f)//TIR
            return 1.0f;
        cosX = sqrt(cosT2);
    }

    float x = 1.0f - cosX;
    return Ro + (1.0f - Ro)* x * x * x * x * x;
}

glm::vec3 RayTracer::Refract(glm::vec3 incident, glm::vec3 normal,float n1, float n2){
    float n = n1 / n2;
    float cos1 = -glm::dot(normal, incident);
    //cos1 = cos1 < 0? cosI : -cosI;
    float cos2 = 1.0 - n * n * (1.0f - cos1 * cos1);

    /*if(cos2 < 0.0f)//TIR
        return glm::vec3(0.0f);*/
    
    cos2 = sqrt(cos2);
    return n * incident + (n * cos1 - cos2) * normal;
}



glm::dvec3 RayTracer::cook_torrance( glm::dvec3 wi, glm::dvec3 wo, IntersectionRecord intersection_record )
{
    glm::dvec3 h = glm::normalize( (wo - wi) / 2.0 );
    double nh  = glm::abs( glm::dot( glm::dvec3( intersection_record.normal_ ), h));
    double nwo = glm::abs( glm::dot( glm::dvec3( intersection_record.normal_ ), wo ));
    double nwi = glm::abs( glm::dot( glm::dvec3( intersection_record.normal_ ), -wi ));
    double hwo = glm::abs( glm::dot( h, wo ));
    double hwi = glm::abs( glm::dot( h, -wi ));

    //Beckmann

    double m = 0.35;
    double nh2 = nh * nh;
    double m2 = m * m;
    double d1 = 1.0 / ( M_PI * m2 * nh2 * nh2);
    double d2 = ( nh2 - 1.0 ) / (m2 * nh2 );
    double D = d1 * glm::exp( d2 );

    //Geometric term

    double g1 = 2.0 * nh / hwo;
    double G = glm::min( 1.0, glm::min(g1 * nwo, g1 * nwi ));

    //Fresnel term

    double one_minus_hwi_5 = ( 1.0 - hwi ) * ( 1.0 - hwi ) * ( 1.0 - hwi ) * ( 1.0 - hwi ) * ( 1.0 - hwi );
    glm::dvec3 F = M_PI * glm::dvec3( intersection_record.brdf_ ) + ( glm::dvec3(1.0) - ( M_PI * glm::dvec3( intersection_record.brdf_ ) ) ) * one_minus_hwi_5;

    //Cook-Torrance

    return ( F * D * G) / ( 4.0 * nwo * nwi );
}


glm::vec3 RayTracer::L( Ray ray, IntersectionRecord intersection_record, size_t curr_depth ) //Rendering equation
{
    glm::vec3 Lo{ 0.0f, 0.0f, 0.0f };
    
    Ray refl_ray;
    
    intersection_record.t_ = std::numeric_limits< double >::max();

    if ( curr_depth < maximum_depth_ )
    {
        if ( scene_.intersect ( ray, intersection_record ))
        {            
            if( intersection_record.pmirror_ )//if its a mirror
            {
                refl_ray = get_reflection(intersection_record, ray);

                Lo = L(refl_ray, intersection_record, ++curr_depth);
            
            }

            else if( intersection_record.glass_ )//if its glass
            {
                float cosX = glm::dot(ray.direction_, intersection_record.normal_);
                float random = rand() / (float)RAND_MAX;
                float n1, n2;

                if(cosX < 0.0f){//Ray is coming from the external media(n1) to internal media(n2)
                    n1 = 1.0f;
                    n2 = 1.5f;
                }
                else{//Ray is coming from the internal media(n1) to external media(n2)
                    n1 = 1.5f;
                    n2 = 1.0f;
                    intersection_record.normal_ = - intersection_record.normal_;
                }
                glm::vec3 newRayDirection;

                float schlick = rSchlick2(ray.direction_, intersection_record.normal_, n1, n2);
                if(random < schlick)
                    newRayDirection = get_reflection(intersection_record, ray).direction_;
                else{
                    newRayDirection = Refract(ray.direction_, intersection_record.normal_, n1, n2);
                }

            refl_ray = {intersection_record.position_ + 0.001f * newRayDirection, newRayDirection};

            Lo = L(refl_ray, intersection_record, ++curr_depth);


            }
                        else if( intersection_record.metal_ )//if its metal
                        {
                            refl_ray = get_new_ray( intersection_record );
                            Lo = intersection_record.emittance_ + glm::vec3( cook_torrance( glm::dvec3( refl_ray.direction_ ), glm::dvec3( ray.direction_ ), intersection_record )) *
                            L( refl_ray, intersection_record, ++curr_depth ) * glm::dot( intersection_record.normal_, refl_ray.direction_ );
            }

            else//if its diffuse  
            {          
                refl_ray = get_new_ray( intersection_record );

                Lo = intersection_record.emittance_ + 2.0f * ((float) M_PI) * intersection_record.brdf_ *
                L( refl_ray, intersection_record, ++curr_depth ) * glm::dot( intersection_record.normal_, refl_ray.direction_ ); 
            }
        }                              
    }
    return Lo;
}
    
void RayTracer::integrate( void )
{
    //Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    Ray ray;
    IntersectionRecord intersection_record;

    #pragma omp parallel for schedule(dynamic, 1) private(ray, intersection_record)

    // Loops over image rows
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        srand(std::time(0));

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
            for(std::size_t i = 0; i < samples_; i++ )
            {   
                //intersection_record.t_ = std::numeric_limits< double >::max();

                float rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                //Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + 0.5f, y + 0.5f } ) };
                ray = { camera_.getWorldSpaceRay( glm::vec2{ x + rand1, y + rand2 } ) };

                //if ( scene_.intersect( ray, intersection_record ) )
                //buffer_.buffer_data_[x][y] = glm::vec3{ intersection_record.t_ * 0.2f };
                //final_color = final_color + intersection_record.color_;
                buffer_.buffer_data_[x][y] += L( ray, intersection_record, 0 );            
            }
            buffer_.buffer_data_[x][y] /= static_cast <float> (samples_);
        }
    }

    std::clog << std::endl;
}
