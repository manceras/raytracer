#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../core/ray.h"
#include "../core/vec3.h"
#include "../core/vertex.h"
#include "geometry.h"

class Triangle : public Geometry {
private:
  Vertex v1;
  Vertex v2;
  Vertex v3;

public:
	Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
  Hit hit(const Ray &ray) const;
	Vec3 normal_at(const Hit &hit) const;
};

#endif
