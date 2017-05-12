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

Ray RayTracer::get_new_ray( IntersectionRecord intersection_record ){

    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float theta = glm::acos( 1 - r1 );
    float phi = 2 * M_PI * r2;
    ONB onb_;

    onb_.setFromV(intersection_record.normal_);

    glm::vec3 cartesian_coordinate{ cosf(phi)*sinf(theta), cosf(theta), sinf(phi)*sinf(theta) };


    return Ray{ intersection_record.position_ + (intersection_record.normal_*0.001f), onb_.getBasisMatrix() * cartesian_coordinate };
}


Ray RayTracer::get_reflection(IntersectionRecord intersection_record, Ray oldray){

    ONB onb_;

    onb_.setFromV(intersection_record.normal_);

    Ray newray;

    glm::vec3 newdir = glm::transpose(onb_.getBasisMatrix()) * oldray.direction_;
    newdir = {newdir.x, -newdir.y, newdir.z};
    newray = {intersection_record.position_ + (intersection_record.normal_*0.001f), onb_.getBasisMatrix() * newdir};

    return newray;


}

double RayTracer::rSchlick2(const glm::vec3 normal, glm::vec3 incident, double n1, double n2){

    double r0 = (n1 - n2) /(n1 + n2);
    r0 *= r0;
    double cosX = -glm::dot(normal, incident);
    if (n1 > n2) {
        const double n = n1/n2;
        const double sinT2 = n * n * (1.0 - cosX * cosX);
        if(sinT2 > 1.0) return 1.0;
        cosX = sqrt(1.0 - sinT2);
    }
    const double x = 1.0 - cosX;
    return r0 + ( 1.0 - r0 ) * x * x * x * x * x;
}


glm::vec3 RayTracer::L( Ray ray, size_t curr_depth ) //Rendering equation
{
    IntersectionRecord intersection_record;
    glm::vec3 Lo{ 0.0f, 0.0f, 0.0f };
    Ray refl_ray;
    
    intersection_record.t_ = std::numeric_limits< double >::max();

    if ( curr_depth < maximum_depth_ )
    {
        if ( scene_.intersect ( ray, intersection_record ))
        {
            
            if(intersection_record.pmirror_){//If its a mirror

                refl_ray = get_reflection(intersection_record, ray);

                Lo = L(refl_ray, ++curr_depth);
            
            }
            else{
                
                if(intersection_record.glass_){//If its glass

                    float n1, n2;
                    
                    if(glm::dot(ray.direction_,intersection_record.normal_)>0){
                        n1 = 1.0f;
                        n2 = 1.3f;
                    }else{
                        n1 = 1.3f;
                        n2 = 1.0f;
                    }

                    double fresnel = rSchlick2(intersection_record.normal_, -(ray.direction_), n1, n2);

                    double r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                    if(r<fresnel){
                        refl_ray = get_reflection(intersection_record, ray);
                        Lo = L(refl_ray, ++curr_depth);
                    }else{
                        const float n = n1/n2;

                        const float cosI = glm::dot(intersection_record.normal_, ray.direction_);

                        const double sinT2 = n * n * (1.0 - cosI * cosI);

                        if (sinT2 > 1.0)
                            return glm::vec3{0.0f,0.0f,0.0f};// TIR

                        const float cosT = glm::sqrt(1.0 - sinT2);
                        refl_ray.direction_ = n * ray.direction_ + (n * cosI - cosT) * intersection_record.normal_;
                        refl_ray.origin_ = intersection_record.position_ + (0.001f*refl_ray.direction_);
                        Lo = L(refl_ray, ++curr_depth);
                    }


                }else{//If its diffuse
            
            refl_ray = get_new_ray( intersection_record );

            Lo = intersection_record.emittance_ + 2.0f * ((float) M_PI) * intersection_record.brdf_ *
            L( refl_ray, ++curr_depth ) * glm::dot( intersection_record.normal_, refl_ray.direction_ ); 

                }
            }
                              
        }
    }
    return Lo;
}

void RayTracer::integrate( void )
{
    //IntersectionRecord intersection_record;

    //glm::vec3 final_color{ 0.0f, 0.0f, 0.0f };

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

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
                Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + rand1, y + rand2 } ) };

                //if ( scene_.intersect( ray, intersection_record ) )
                //buffer_.buffer_data_[x][y] = glm::vec3{ intersection_record.t_ * 0.2f };
                //final_color = final_color + intersection_record.color_;
                buffer_.buffer_data_[x][y] += L( ray, 0 );            
            }

            //buffer_.buffer_data_[x][y] = glm::vec3{ final_color / static_cast <float> (samples_) };
            buffer_.buffer_data_[x][y] /= static_cast <float> (samples_);
            //final_color = { 0.0f, 0.0f, 0.0f };
        }
    }

    std::clog << std::endl;
}

