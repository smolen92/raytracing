#ifndef _HITLIST_H_
#define _HITLIST_H_

#include "hittable.h"

/// \file



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

