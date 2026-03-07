#include "light.h"

Light::Light(Vec3 position, float intensity)
    : position(position), intensity(intensity) {}

float Light::multiplier_for_point(Vec3 normal, Vec3 point) {
	Vec3 impact_to_light = (position - point).normalize();
  float dot = normal * impact_to_light;
	if (dot < 0) return 0;
  return intensity * dot;
}
