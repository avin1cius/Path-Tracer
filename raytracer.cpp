#include "raytracer.h"

RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      const size_t samples,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        samples_{ samples},
        buffer_( buffer )
{}

void RayTracer::integrate( void )
{
    IntersectionRecord intersection_record;

    glm::vec3 final_color;

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
           intersection_record.t_ = std::numeric_limits< double >::max();

            for(std::size_t i = 0; i < samples_; i++ )
            {
                float rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + 0.5f, y + 0.5f } ) };
                //Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + rand1, y + rand2 } ) };

                if ( scene_.intersect( ray, intersection_record ) )
                    //buffer_.buffer_data_[x][y] = glm::vec3{ intersection_record.t_ * 0.2f };
                    final_color = final_color + intersection_record.color_;

                    buffer_.buffer_data_[x][y] = glm::vec3{ final_color / samples_ };
            }
        }
    }

    std::clog << std::endl;
}

