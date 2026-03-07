#ifndef LIGHT_H
#define LIGHT_H

#include "../core/vec3.h"
#include "../core/rgb_color.h"

class Light {
private:
	Vec3 position;
	RGBColor intensity;

public:
	Light(Vec3 position, RGBColor intensity);
	RGBColor multiplier_for_point(Vec3 normal, Vec3 point);
};

#endif
