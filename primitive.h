#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "ray.h"
#include "intersection_record.h"
#include "bbox.h"

class Primitive
{
public:

    typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

    Primitive( void );

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;

    virtual BBox getAABB( void ) const = 0;

    glm::vec3 color_ = { 0.0f, 0.0f, 0.0f };
};

#endif /* PRIMITIVE_H_ */

