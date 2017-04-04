#include "triangle.h"

Triangle::Triangle( void )
{}

Triangle::Triangle( const glm::vec3 &p1,const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 &brdf, const glm::vec3 &emittance ) :
	p1_{ p1 },
	p2_{ p2 },
	p3_{ p3 },
	brdf_{ brdf },
	emittance_{ emittance }
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const
{
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

	float ei_minus_hf = e*i - h*f;
	float gf_minus_di = g*f - d*i;
	float dh_minus_eg = d*h - e*g;
	float ak_minus_jb = a*k - j*b;
	float jc_minus_al = j*c - a*l;
	float bl_minus_kc = b*l - k*c;

	float M = a*(ei_minus_hf) + b*(gf_minus_di) + c*(dh_minus_eg);	

	float t = -(f*(ak_minus_jb) + e*(jc_minus_al) + d*(bl_minus_kc))/M;	

	if(t < 0.0f)
		return false;	

	float gama = (i*(ak_minus_jb) + h*(jc_minus_al) + g*(bl_minus_kc))/M;

	if(gama < 0.0f || gama > 1.0f)

		return false;

	float beta = (j*(ei_minus_hf) + k*(gf_minus_di) + l*(dh_minus_eg))/M;

	if(beta < 0.0f || beta > (1.0f - gama))
		return false;

	//glm::vec3 center_ = glm::vec3((p1_.x+p2_.x+p3_.x)/3.0f , (p1_.y+p2_.y+p3_.y)/3.0f , (p1_.z+p2_.z+p3_.z)/3.0f);

	intersection_record.t_ =  t;
	intersection_record.position_ = ray.origin_ +intersection_record.t_ * ray.direction_;
	
	intersection_record.normal_ = glm::normalize( glm::cross(p2_ - p1_, p3_ - p1_));
	if (glm::dot(intersection_record.normal_, ray.direction_) > 0)
        intersection_record.normal_ = -intersection_record.normal_;

	intersection_record.brdf_ = brdf_;
	intersection_record.emittance_ = emittance_;

	return true;
}

