#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    glm::vec3 brdf_;
    glm::vec3 emittance_;
    bool pmirror_;
    bool glass_;
    bool metal_;
};

#endif /* INTERSECTION_RECORD_H_ */

