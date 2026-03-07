#include "viewport.h"
#include "ray.h"
#include "vec3.h"

Viewport::Viewport(int width, int height) : width(width), height(height) {}

Ray Viewport::rayForPx(int column, int row) {
  float normalized_i = (float)column / width;
  float normalized_j = (float)row / height;

  float aspect_ratio = (float)width / height;
  float pixel_aspect = 0.5;

  float x = (2.0 * normalized_i - 1.0) * aspect_ratio * pixel_aspect;
  float y = 1.0 - 2.0 * normalized_j;

  Vec3 point = Vec3(x, y, 1);

  Vec3 origin = Vec3(0, 0, 0);
  Vec3 direction = point.normalize();

  return Ray(origin, direction);
}
