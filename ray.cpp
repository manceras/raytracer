#include "vec3.h"

class Ray {
public:
  Vec3 point, direction;

  Ray(const Vec3 &point, const Vec3 &direction)
      : point(point), direction(direction) {}

  Vec3 at(float t) { return point + t * direction; }
};
