#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../core/vec3.h"
#include "../core/ray.h"

class Geometry {
	public:
		virtual float collides(Ray &ray) = 0;
		virtual Vec3 normal_at_point(const Vec3 &point) = 0;
};

#endif
