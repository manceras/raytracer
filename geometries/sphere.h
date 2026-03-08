#ifndef SPHERE_H
#define SPHERE_H

#include "../core/ray.h"
#include "../core/vec3.h"
#include "geometry.h"

class Sphere : public Geometry {
private:
  float radius;
  Vec3 center;

public:
	Sphere(float r, const Vec3 c);
  float collides(Ray &ray);
	Vec3 normal_at_point(const Vec3 &point);
};

#endif
