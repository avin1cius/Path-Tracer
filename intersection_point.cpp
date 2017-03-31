#include "intersection_point.h"


Ray IntersectionPoint::get_new_ray( IntersectionRecord intersection_record ){

    float r1 = rand();
    float r2 = rand();
    float theta = arccos( 1 - r1 );
    float phi = 2 * pi * r2;

    glm::vec3 cartesian_coordinate{-cosf(phi)*sinf(theta), sinf(phi), -cosf(phi)*cos(theta)};

    if(glm::dot( intersection_record.normal_, onb_.getBasisMatrix() * cartesian_coordinate ) < 0.0f )
    {
        cartesian_coordinate = -cartesian_coordinate;
    }

    return Ray{ intersection_record.position_ , cartesian_coordinate };
}