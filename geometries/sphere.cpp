#include "sphere.h"
#include "../ray.h"
#include "../vec3.h"
#include <cmath>

Sphere::Sphere(float r, const Vec3 c) : radius(r), center(c) {}

float Sphere::collides(Ray &ray) {
  float a = ray.direction * ray.direction;
  Vec3 l = ray.point - center;
  float b = 2 * (ray.direction * l);
  float c = (l * l) - radius * radius;

  float discriminant = sqrt(b * b - 4 * a * c);

  float t1 = (-b + discriminant) / (2 * a);
  float t2 = (-b - discriminant) / (2 * a);

  if (t1 > 0)
    return t1;
  if (t2 > 0)
    return t2;
  return -1;
}
