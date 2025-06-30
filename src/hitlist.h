#ifndef _HITLIST_H_
#define _HITLIST_H_

#include "hittable.h"
#include "interval.h"

#include <vector>

class hitlist : public hittable {
	public:
		std::vector<hittable*> objects;

		hitlist();
		hitlist(hittable* object);

		void clear();
		void add(hittable* object);

		bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif

