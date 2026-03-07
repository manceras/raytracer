#include "ray.h"
#include "vec3.h"

class Viewport {
private:
  float distance = 1;
  int width, height;

public:

	Viewport(int width, int height): width(width), height(height) {}

  Ray rayForPx(int i, int j) {
    float normalized_i = (float)i / width;
    float normalized_j = (float)j / height;

    float aspect_ratio = (float)width / height;
    float pixel_aspect = 0.5;

    float x = (2.0 * normalized_i - 1.0) * aspect_ratio * pixel_aspect;
    float y = 1.0 - 2.0 * normalized_j;

    Vec3 point = Vec3(x, y, 1);

    Vec3 origin = Vec3(0, 0, 0);
    Vec3 direction = point.normalize();

    return Ray(origin, direction);
  }
};
