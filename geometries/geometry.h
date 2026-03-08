#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../core/vec3.h"
#include "../core/ray.h"

class Geometry {
	public:
		virtual float collides(const Ray &ray) const = 0;
		virtual Vec3 normal_at_point(const Vec3 &point) const = 0;
};

#endif
