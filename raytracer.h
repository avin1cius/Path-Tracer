#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include "camera.h"
#include "scene.h"
#include "buffer.h"

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

    Ray get_reflection( IntersectionRecord, Ray);

    glm::vec3 L( Ray, IntersectionRecord, size_t );

    double rSchlick1(const glm::vec3 normal, glm::vec3 incident, double n1, double n2);

    double rSchlick2(const glm::vec3 normal, glm::vec3 incident, double n1, double n2);

    glm::dvec3 cook_torrance( glm::vec3 wi, glm::vec3 wo, IntersectionRecord intersection_record );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    const size_t samples_;
    const size_t maximum_depth_;

    Buffer &buffer_;

};

#endif /* RAYTRACER_H_ */

