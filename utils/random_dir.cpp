#include "random_dir.h"
#include <cmath>
#include <cstdlib>

float random_number_normal_distribution() {
	float theta = 2 * 3.1415926 * ( (float)rand() / RAND_MAX );
	float rho = std::sqrt(-2 * std::log((float)rand() / RAND_MAX));
	return rho * cos(theta);
}

Vec3 random_direction() {
	float x = random_number_normal_distribution();
	float y = random_number_normal_distribution();
	float z = random_number_normal_distribution();
	return Vec3(x, y, z).normalize();
}
