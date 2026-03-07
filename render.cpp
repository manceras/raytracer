#include "geometries/sphere.h"
#include "lights/light.h"
#include "core/vec3.h"
#include "core/viewport.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  int height = 22;
  int width = 80;
  string characters = " .:-=+*#%@";

  Viewport viewport = Viewport(width, height);

  Sphere sphere = Sphere(1, Vec3(0, 0, 2));

  Light light1 = Light(Vec3(0, 0, 0.1), 1);
  Light light2 = Light(Vec3(0, 1, 0.1), 1);

	const int lights_length = 2;
	Light * lights[lights_length] = {&light1, &light2};

  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {

      Ray ray = viewport.rayForPx(column, row);
      float distance = sphere.collides(ray);

      if (distance < 0) {
        cout << " ";
        continue;
      }

      Vec3 impact_point = ray.at(distance);

      Vec3 normal = sphere.normal_at_point(impact_point);

			float multiplier = 0;

			for (int i = 0; i < lights_length; i++) {
				Light * light = lights[i];
				multiplier += light->multiplier_for_point(normal, impact_point);
			}

      int brightness = (int)(multiplier * characters.length());

      if (brightness >= 10 || brightness < 0) {
        brightness = 9;
      }

      cout << characters[brightness];
    }
    cout << endl;
  }
}
