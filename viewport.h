#include "ray.h"
#include "vec3.h"

class Viewport {
private:
  float distance = 1;
  int width, height;

public:
	Viewport(int width, int height);
  Ray rayForPx(int i, int j);
};
