#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../core/ray.h"
#include "../core/vec3.h"
#include "geometry.h"

class Triangle : public Geometry {
private:
  Vec3 v1;
  Vec3 v2;
  Vec3 v3;

public:
	Triangle(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);
  float collides(const Ray &ray) const;
	Vec3 normal_at_point(const Vec3 &point) const;
};

#endif
