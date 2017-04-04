#include "intersection_point.h"

IntersectionPoint::IntersectionPoint( void )
{}

IntersectionPoint::IntersectionPoint( const glm::vec3 &Le, const glm::vec3 &fr, glm::vec3 &normal )
{
    Le_ = Le;
    fr_ = fr / (float)M_PI;
    normal_ = normal;
}