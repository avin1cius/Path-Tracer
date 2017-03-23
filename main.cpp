#include "main.h"

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;

    /*OrthographicCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at
    */
    PerspectiveCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
                                1.00f, // distance
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 0.0f, 2.0f },     // position
                                glm::vec3{ 0.0f, 1.0f, 0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at
    Scene scene{};
    char obj[20] = "object1.obj";

    //scene.load();
    scene.loadObject(obj);

    Buffer rendering_buffer{ x_resolution, y_resolution };
    size_t samples = 1; //samples per pixel
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    RayTracer rt( camera,
                  scene,
                  background_color,
                  samples,
                  rendering_buffer );

    rt.integrate(); // Renders the final image.

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image.ppm" );

    return EXIT_SUCCESS;
}

