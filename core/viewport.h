#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "ray.h"
#include "vec3.h"

class Viewport {
private:
  Vec3 origin;
  Vec3 direction;
  float focal_length;
  int width, height;

	Vec3 up;
	Vec3 right;

public:
  Viewport(int width, int height, Vec3 origin, float focal_length,
           Vec3 look_at);
  Ray rayForPx(int column, int row);
};

#endif
