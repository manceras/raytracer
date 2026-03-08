#include "viewport.h"
#include "ray.h"
#include "vec3.h"

Viewport::Viewport(int width, int height, Vec3 origin, float focal_length,
                   Vec3 look_at)
    : width(width), height(height), origin(origin), focal_length(focal_length),
      direction((look_at - origin).normalize()),
      right(direction.cross(Vec3(0, 1, 0))), up(direction.cross(right)) {}

Ray Viewport::rayForPx(int column, int row) const {
  float normalized_i = (float)column / width;
  float normalized_j = (float)row / height;

  float aspect_ratio = (float)width / height;
  float pixel_aspect = 1;

  Vec3 forward = direction;
  Vec3 right = direction.cross(Vec3(0, 1, 0));
  Vec3 up = right.cross(forward);

  float x = (2.0 * normalized_i - 1.0) * aspect_ratio * pixel_aspect;
  float y = 1.0 - 2.0 * normalized_j;

  Vec3 point = origin + forward * focal_length + right * x + up * y;

  return Ray(origin, (point - origin).normalize());
}
