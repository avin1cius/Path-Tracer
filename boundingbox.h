#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>
#include "primitive.h"
#include "ray.h"
#include "intersection_record.h"

class BoundingBox : public Primitive
{

    public:
    BoundingBox();

    BoundingBox(const glm::vec3 &min, const glm::vec3 &max);

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;
                    
    glm::vec3 min_;
    glm::vec3 max_;
    glm::vec3 center_;

};

#endif /*BOUNDINGBOX_H_*/