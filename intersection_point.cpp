#include "intersection_point.h"


IntersectionPoint::IntersectionPoint(const glm::vec3 Le_, const glm::vec3 fr_, glm::vec3 normal){
    Le = Le_;
    fr = fr_ / (float)M_PI;
    normal_ = normal;
}


Ray IntersectionPoint::get_new_ray( IntersectionRecord intersection_record ){

    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float theta = glm::acos( 1 - r1 );
    float phi = 2 * M_PI * r2;
    ONB onb_;

    onb_.setFromV(intersection_record.normal_);

    glm::vec3 cartesian_coordinate{-cosf(phi)*sinf(theta), sinf(phi), -cosf(phi)*cos(theta)};


    return Ray{ intersection_record.position_ , onb_.getBasisMatrix() * cartesian_coordinate - intersection_record.position_ };
}