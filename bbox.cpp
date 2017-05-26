#include "bbox.h"

double BBox::getArea( void ) const
{
    double l = ( max_.x - min_.x );
    double m = ( max_.y - min_.y );
    double n = ( max_.z - min_.z );
    return 2.0 * ( l * ( m + n ) + m * n );
}

bool BBox::intersect( const Ray &ray ) const
{
    glm::vec3 invdir = (1.0f/ray.direction_);

    int sign[3];

    sign[0] = (invdir.x < 0);
    sign[1] = (invdir.y < 0);
    sign[2] = (invdir.z < 0);

    glm::vec3 bounds[2];
    bounds[0] = min_;
    bounds[1] = max_;

    float tmin = ( bounds[sign[0]].x - ray.origin_.x ) * invdir.x;
    float tmax = ( bounds[1 - sign[0]].x - ray.origin_.x ) * invdir.x;
    float tymin = ( bounds[sign[1]].y - ray.origin_.y ) * invdir.y;
    float tymax = ( bounds[1 - sign[1]].y - ray.origin_.y ) * invdir.y; 

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax; 

    float tzmin = (bounds[sign[2]].z - ray.origin_.z) * invdir.z;
    float tzmax = (bounds[1 - sign[2]].z - ray.origin_.z) * invdir.z; 

    if ((tmin > tzmax) || (tzmin > tmax))
    return false;

    if (tzmin > tmin)
    tmin = tzmin;

    if (tzmax < tmax)
    tmax = tzmax;

    return true; 

}