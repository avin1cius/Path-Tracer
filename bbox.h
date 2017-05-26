#ifndef BBOX_H_
#define BBOX_H_

#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>
//#include "primitive.h"
#include "ray.h"
#include "intersection_record.h"

class BBox
{
  public:

    BBox()
    {};

    BBox( const glm::dvec3 &min,
          const glm::dvec3 &max ) :
            min_{ min },
            max_{ max },
            centroid_{ 0.5 * ( min_ + max_ ) }
    {};

    ~BBox( void ){};

    double getArea( void ) const;

    bool intersect( const Ray &ray ) const;

    BBox operator + ( const BBox &rhs ) const
    {
        return BBox{ glm::min( min_, rhs.min_ ),
                     glm::max( max_, rhs.max_ ) };
    }

    glm::dvec3 min_;

    glm::dvec3 max_;

    glm::dvec3 centroid_;

};

#endif /*BBOX_H_*/