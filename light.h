#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
class Light {
private:
	Vec3 position;
	float intensity;

public:
	Light(Vec3 position, float intensity);
	float multiplier_for_point(Vec3 normal, Vec3 point);
};

#endif
