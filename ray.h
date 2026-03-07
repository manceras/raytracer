#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
	public:
		Vec3 point, direction;
		Ray(const Vec3 &point, const Vec3 &direction);
		Vec3 at(float t);
};

#endif
