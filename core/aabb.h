#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "ray.h"

class AABB {
private:
	Vec3 min;
	Vec3 max;

public:
	AABB(const Vec3 min, const Vec3 max);
	bool hit(const Ray &ray) const;
};

#endif
