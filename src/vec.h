#ifndef _VEC3_H_
#define _VEC3_H_

#include "constant.h"

#include <iostream>

/// \file

class vec3 {
	public:
		float x,y,z;
		
		vec3(float tx=0, float ty=0, float tz=0);
		float length() const;
		float length_squared() const;
		vec3 operator-() const;
		vec3& operator+=(const vec3& v);
		vec3& operator*=(float t);
		vec3& operator/=(float t);
		
		vec3 random();
		vec3 random(float min, float max);
		bool near_zero() const;

};

using point3 = vec3;

std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(float t, const vec3& v);
vec3 operator*(const vec3& v, float t);
vec3 operator/(float t, const vec3& v);
vec3 operator/(const vec3& v, float t);
float dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 get_unit_vector(const vec3& v);
vec3 random_on_hemisphere(const vec3& normal);
vec3 random_unit_vector();
vec3 reflect(const vec3& v, const vec3& n);
vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat);
vec3 random_in_unit_disk();

#endif
