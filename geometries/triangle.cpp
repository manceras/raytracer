#include "triangle.h"
#include "../core/ray.h"
#include "../core/vec3.h"

Triangle::Triangle(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
    : v1(v1), v2(v2), v3(v3) {}

float determinant(const Vec3 &c1, const Vec3 &c2, const Vec3 &c3) {
  return c1 * (c2.cross(c3));
}

float Triangle::collides(const Ray &ray) const {
  Vec3 minus_direction =
      Vec3(-ray.direction.x, -ray.direction.y, -ray.direction.z);
  Vec3 e1 = v2 - v1;
  Vec3 e2 = v3 - v1;
  float original_matrix_det = determinant(minus_direction, e1, e2);

  if (original_matrix_det == 0)
    return -1;

  Vec3 b = ray.point - v1;
  float t = determinant(b, e1, e2) / original_matrix_det;
  float u = determinant(minus_direction, b, e2) / original_matrix_det;
  float v = determinant(minus_direction, e1, b) / original_matrix_det;

  if (u < 0 || u > 1 || v < 0 || v > 1 || u + v > 1) {
    return -1;
  }

  return t;
}

Vec3 Triangle::normal_at_point(const Vec3 &point) const {
  Vec3 e1 = v2 - v1;
  Vec3 e2 = v3 - v1;
  Vec3 vector = e1.cross(e2);
  return vector.normalize();
}
