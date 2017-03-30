#ifndef INTERSECTION_POINT_H_
#define INTERSECTION_POINT_H_

#include <glm/glm.hpp>
#include "intersection_record.h"
#include "ray.h"
#include "onb.h"

class IntersectionPoint{

public:

    glm::vec3 Le;
    glm::vec3 fr;
    glm::vec3 normal;
    glm::vec3 pos

    Ray get_new_ray(IntersectionRecord intersection_record);


}
#endif /* INTERSECTION_POINT_H_ */