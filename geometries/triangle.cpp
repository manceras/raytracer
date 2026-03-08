#include "triangle.h"
#include "../core/ray.h"
#include "../core/vec3.h"
#include "../core/vertex.h"
#include "geometry.h"

Triangle::Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
    : v1(v1), v2(v2), v3(v3) {}

float determinant(const Vec3 &c1, const Vec3 &c2, const Vec3 &c3) {
  return c1 * (c2.cross(c3));
}

Hit Triangle::hit(const Ray &ray) const {
  Vec3 minus_direction =
      Vec3(-ray.direction.x, -ray.direction.y, -ray.direction.z);
  Vec3 e1 = v2.position - v1.position;
  Vec3 e2 = v3.position - v1.position;
  float original_matrix_det = determinant(minus_direction, e1, e2);

  if (original_matrix_det == 0)
    return {-1, 0, 0};

  Vec3 b = ray.point - v1.position;
  float t = determinant(b, e1, e2) / original_matrix_det;
  float u = determinant(minus_direction, b, e2) / original_matrix_det;
  float v = determinant(minus_direction, e1, b) / original_matrix_det;

  if (u < 0 || u > 1 || v < 0 || v > 1 || u + v > 1) {
    return {-1, 0, 0};
  }

  return {t, u, v};
}

Vec3 Triangle::normal_at(const Hit &hit) const {
	float u = hit.u;
	float v = hit.v;
	float w = 1 - u - v;

	return u * v1.normal + v * v2.normal + w * v3.normal;
}
