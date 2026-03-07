#include "../ray.h"
#include "../vec3.h"

class Sphere {
private:
  float radius;
  Vec3 center;

public:
	Sphere(float r, const Vec3 c);
  float collides(Ray &ray);
};
