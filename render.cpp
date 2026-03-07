#include "geometries/sphere.h"
#include "light.h"
#include "vec3.h"
#include "viewport.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  int height = 22;
  int width = 80;
  string characters = ".:-=+*#%@";

  Viewport viewport = Viewport(width, height);

  Sphere sphere = Sphere(1, Vec3(0, 0, 2));

  Light light = Light(Vec3(0, 0, -3), 1);

  string saved = "not saved";

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
      float multiplier = light.multiplier_for_point(normal, impact_point);

      if (row == 11 && column == 40) {
        saved = "Multipler result is " + to_string(multiplier) + "\n";
        saved += "Normal x: " + to_string(normal.x) + "\n";
        saved += "Normal y: " + to_string(normal.y) + "\n";
        saved += "Normal z: " + to_string(normal.z) + "\n";
        saved += "impact x:" + to_string(impact_point.x) + "\n";
        saved += "impact y:" + to_string(impact_point.y) + "\n";
        saved += "impact z:" + to_string(impact_point.z) + "\n";
      }

      int brightness = (int)(multiplier * characters.length());

      if (brightness >= 10 || brightness < 0) {
        brightness = 9;
      }

      cout << characters[brightness];
    }
    cout << endl;
  }

  cout << endl;
  cout << endl;
  cout << "multiplier at 10 30 is " << saved << endl;
}
