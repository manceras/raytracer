#include "../ray.h"
#include "../vec3.h"

class Sphere {
private:
  float radius;
  Vec3 center;

public:
  float collides(Ray &ray);
};
