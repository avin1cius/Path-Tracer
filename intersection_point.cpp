#include "intersection_point.h"


Ray get_new_ray(IntersectionRecord intersection_record){

        float r1 = rand();
        float r2 = rand();
        float theta = arccos( 1 - r1 );
        float phi = 2 * pi * r2;

        glm::vec3 cartesianCoordinate{-cosf(phi)*sinf(theta), sinf(phi), -cosf(phi)*cos(theta)};

        if(glm:: dot(intersection_record.normal_, onb_.getBasisMatrix() * cartesianCoordinate) < 0.0f){

            cartesianCoordinate = -cartesiancoordinate;
        }

        return Ray{ intersection_record.position_ , cartesianCoordinate };
}