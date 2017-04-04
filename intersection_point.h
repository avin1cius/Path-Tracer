#ifndef INTERSECTION_POINT_H_
#define INTERSECTION_POINT_H_

#include <glm/glm.hpp>
#include "intersection_record.h"
#include "ray.h"
#include "onb.h"

class IntersectionPoint{

public:

    IntersectionPoint( void );
    IntersectionPoint( const glm::vec3 &Le, const glm::vec3 &fr, glm::vec3 &normal );

    glm::vec3 Le_;
    glm::vec3 fr_;
    glm::vec3 normal_;

};
#endif /* INTERSECTION_POINT_H_ */