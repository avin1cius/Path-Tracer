#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#include "intersection_point.h"

class RayTracer
{
public:

    RayTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               const size_t samples,
               const size_t maximum_depth,
               Buffer &buffer );

    void integrate( void );

    Ray get_new_ray( IntersectionRecord );

    glm::vec3 L( Ray, size_t );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    const size_t samples_;
    const size_t maximum_depth_;

    Buffer &buffer_;

};

#endif /* RAYTRACER_H_ */

