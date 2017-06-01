#include "main.h"

int main( void )
{
    unsigned int x_resolution = 960;
    unsigned int y_resolution = 540;

    /*OrthographicCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at
    */
    PerspectiveCamera camera{  -4.00f, 
                                4.00f,
                               -2.25f, 
                                2.25f,
                                4.00f, // distance
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 1.0f, 4.0f },     // position
                                glm::vec3{ 0.0f, 1.0f, 0.0f },     // up
                                glm::vec3{ 0.0f, 1.0f, 0.0f } };   // look at
    Scene scene{};

    scene.load();
    scene.loadObject("orns.obj");
    scene.acceleration_structure_ = scene.BVH_SAH;
    scene.buildAccelerationStructure();

    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };
    size_t samples = 30; //samples per pixel
    size_t maximum_depth = 5;
    Buffer rendering_buffer{ x_resolution, y_resolution };
    
    // Set up the renderer.
    RayTracer rt( camera,
                  scene,
                  background_color,
                  samples,
                  maximum_depth,
                  rendering_buffer );

    rt.integrate(); // Renders the final image.

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image.ppm" );

    return EXIT_SUCCESS;
}

