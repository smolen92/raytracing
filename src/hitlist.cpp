#include "hitlist.h"


hitlist::hitlist() {
}

hitlist::hitlist(hittable* object) {
	this->add(object);
}
	
void hitlist::clear() {
	for(int i=0; i < objects.size(); i++){
		delete objects[i];
		objects[i] = nullptr;
	}

	/*while( !objects.empty() ) {
		delete objects.back();
		objects.pop_back();
	}*/
}
			
void hitlist::add(hittable* object) {
	objects.push_back(object);
}

bool hitlist::hit(const ray& r, interval ray_t, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = ray_t.max;

	for( int i=0; i < objects.size(); i++) {
		if(objects[i]->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

