#ifndef INTERSECTION_POINT_H_
#define INTERSECTION_POINT_H_

#include <glm/glm.hpp>

struct IntersectionPoint
{
    glm::vec3 Le_;
    glm::vec3 BRDF_;
    glm::vec3 normal_;
};

#endif /* INTERSECTION_POINT_H_ */