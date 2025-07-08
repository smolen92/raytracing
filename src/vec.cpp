#include "vec.h"

vec3::vec3(float tx, float ty, float tz) {
	x = tx;
	y = ty;
	z = tz;
}

float vec3::length() const{
	return std::sqrt(length_squared());
}

float vec3::length_squared() const {
	return x*x + y*y + z*z;
}

vec3 vec3::operator-() const{
	return vec3(-x,-y,-z);
}

vec3& vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3& vec3::operator*=(float t) {
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

vec3& vec3::operator/=(float t) {
	return *this *= (1/t);
}

vec3 vec3::random() {
	return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(float min, float max) {
	return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

bool vec3::near_zero() const {
	float s = 1e-8;
	return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
}

vec3 random_unit_vector() {
	while(true) {
		vec3 temp;
		vec3 p = temp.random(-1,1);
		float lensq = p.length_squared();
		if ( 1e-80 < lensq ) {
			return p / sqrt(lensq);
		}
	}
}

vec3 random_on_hemisphere(const vec3& normal) {
	vec3 on_unit_sphere = random_unit_vector();
	if( dot(on_unit_sphere, normal) > 0.0) {
		return on_unit_sphere;
	}
	else {
		return -on_unit_sphere;
	}
}

vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.x+v.x, u.y+v.y, u.z+v.z);
}

vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.x-v.x, u.y-v.y, u.z-v.z);
}

vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.x*v.x, u.y*v.y, u.z*v.z);
}

vec3 operator*(float t, const vec3& v) {
	return vec3(t*v.x,t*v.y,t*v.z);
}

vec3 operator*(const vec3& v, float t) {
	return t*v;
}

vec3 operator/(float t, const vec3& v) {
	return (1/t) * v;
}

vec3 operator/(const vec3& v, float t) {
	return t/v;
}

float dot(const vec3& u, const vec3& v) {
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

vec3 cross(const vec3& u, const vec3& v) {
	return vec3( u.y*v.z - u.z*v.y,
		     u.z*v.x - u.x*v.z,
		     u.x*v.y - u.y*v.x);
}

vec3 get_unit_vector(const vec3& v) {
	return v / v.length();
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat) {
	float cos_theta = std::fmin(dot(-uv, n),1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
	vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

vec3 random_in_unit_disk() {
	while (true) {
		vec3 p = vec3(random_double(-1,1),random_double(-1,1),0);
		if( p.length_squared() < 1) {
			return p;
		}
	}
}

