#include "vec3.h"

class Ray {
	public:
		Vec3 point, direction;
		Vec3 at(float t);
};
