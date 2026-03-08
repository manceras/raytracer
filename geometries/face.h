#ifndef FACE_H
#define FACE_H

#include "../core/ray.h"
#include "../core/vec3.h"
#include "../core/vertex.h"

struct Hit {
  float t;
  float u;
  float v;
};

class Face {
private:
  Vertex v1;
  Vertex v2;
  Vertex v3;

public:
	Face(const Vertex &v1, const Vertex &v2, const Vertex &v3);
  Hit hit(const Ray &ray) const;
	Vec3 normal_at(const Hit &hit) const;
};

#endif
