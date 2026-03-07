#include "ray.h"

Ray::Ray(const Vec3 &point, const Vec3 &direction)
      : point(point), direction(direction) {}

Vec3 Ray::at(float t) { return point + t * direction; }
