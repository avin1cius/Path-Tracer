#include "triangle.h"

Triangle::Triangle( void )
{}

Triangle::Triangle( const glm::vec3 &p1,const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 color) :
        p1_{ p1 },
        p2_{ p2 },
	p3_{ p3 },
	color_{ color }
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const
{
    
	/*[a d g]
      	  [b e h]
          [c f i]

    a = Xa - Xb
    b = Ya - Yb
    c = Za - Zb
    d = Xa - Xc
    e = Ya - Yc
    f = Za - Zc
    g = Xd
    h = Yd
    i = Zd
    j = Xa - Xe
    k = Ya - Ye
    l = Za - Ze

    
    M = a(ei − hf ) + b(gf − di) + c(dh − eg)

    β = (j(ei − hf ) + k(gf − di) + l(dh − eg)) / M

    γ = (i(ak − jb) + h(jc − al) + g(bl − kc)) / M

    t = -(f (ak − jb) + e(jc − al) + d(bl − kc)) / M

 */
	

	float a,b,c,d,e,f,g,h,i,j,k,l;
	
	a = (p1_.x - p2_.x);
	b = (p1_.y - p2_.y);
	c = (p1_.z - p2_.z);
	d = (p1_.x - p3_.x);
	e = (p1_.y - p3_.y);
	f = (p1_.z - p3_.z);
	g = ray.direction_.x;
	h = ray.direction_.y;
	i = ray.direction_.z;
	j = (p1_.x - ray.origin_.x);
	k = (p1_.y - ray.origin_.y);
	l = (p1_.z - ray.origin_.z);
	
	
	float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

	float t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;

	if(t < 0.0f)
		return false;

	float gama = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;

	if(gama < 0.0f || gama > 1.0f)
		return false;

	float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;


	if(beta < 0.0f || beta > (1.0f - gama))
		return false;

	glm::vec3 center_ = glm::vec3((p1_.x+p2_.x+p3_.x)/3.0f , (p1_.y+p2_.y+p3_.y)/3.0f , (p1_.z+p2_.z+p3_.z)/3.0f);

	intersection_record.t_ =  t;
    	intersection_record.position_ = ray.origin_ +intersection_record.t_ * ray.direction_;
    	intersection_record.normal_ = glm::normalize( intersection_record.position_ - center_);
		intersection_record.color_ = color_;
	return true;

}

