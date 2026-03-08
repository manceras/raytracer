#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../core/ray.h"
#include "../core/vec3.h"

struct Hit {
  float t;
  float u;
  float v;
};

class Geometry {
public:
  virtual Hit hit(const Ray &ray) const = 0;
  virtual Vec3 normal_at(const Hit &hit) const = 0;
};

#endif
