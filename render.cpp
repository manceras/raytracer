#include "geometries/sphere.h"
#include "vec3.h"
#include "viewport.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	int height = 22;
	int width = 80;
	string characters = "@%#*+=-:. ";

	Viewport viewport = Viewport(width, height);

	Sphere sphere = Sphere(1, Vec3(0, 0, 3));

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			Ray ray = viewport.rayForPx(column, row);
			float distance = sphere.collides(ray);
			int discrete_distance = (int)distance;

			if (discrete_distance >= 10 || discrete_distance < 0) {
				discrete_distance = 9;
			}

			cout << characters[discrete_distance];

		}
		cout << endl;
	}
}
