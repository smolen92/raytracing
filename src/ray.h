#ifndef _RAY_H_
#define _RAY_H_

#include "vec.h"

class ray {
	public:
		ray();
		ray(const point3& origin, const vec3& direction);
		point3 at(float t) const;
		
		const point3& origin() const;
		const vec3& direction() const;

	private:
		point3 orig;
		vec3 dir;
};

#endif
