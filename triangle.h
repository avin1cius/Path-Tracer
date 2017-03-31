#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive
{
public:

    Triangle( void );

    Triangle( const glm::vec3 &p1,const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 color, int material);

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 p1_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 p2_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 p3_ = { 0.0f, 0.0f, 0.0f };

    glm::vec3 color_ = { 0.0f, 0.0f, 0.0f};

    int material_;


private:

    static const float kIntersectionTestEpsilon_;
};

#endif /* TRIANGLE_H_ */

