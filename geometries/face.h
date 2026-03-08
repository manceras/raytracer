#ifndef FACE_H
#define FACE_H

#include "../core/material.h"
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
  Material material;

public:
  Face(const Vertex &v1, const Vertex &v2, const Vertex &v3,
       const Material &material);
  Face();
  Hit hit(const Ray &ray) const;
  Vec3 normal_at(const Hit &hit) const;
  Material get_material() const { return material; }
  Vertex get_v1() const { return v1; }
  Vertex get_v2() const { return v2; }
  Vertex get_v3() const { return v3; }
  Vec3 centroid() const {
    return (v1.position + v2.position + v3.position) * (1.0 / 3);
  }
};

#endif
