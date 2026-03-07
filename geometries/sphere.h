#ifndef SPHERE_H
#define SPHERE_H

#include "../ray.h"
#include "../vec3.h"

class Sphere {
private:
  float radius;
  Vec3 center;

public:
	Sphere(float r, const Vec3 c);
  float collides(Ray &ray);
	Vec3 normal_at_point(const Vec3 &point);
};

#endif
