#include "light.h"

Light::Light(Vec3 position, RGBColor intensity)
    : position(position), intensity(intensity) {}

RGBColor Light::multiplier_for_point(Vec3 normal, Vec3 point) {
  Vec3 impact_to_light = position - point;
  float dot = normal * impact_to_light.normalize();
  float distance = impact_to_light.modulus();
  if (dot < 0)
    return RGBColor(0, 0, 0);

  return RGBColor(intensity.red * dot / (distance * distance),
                  intensity.green * dot / (distance * distance),
                  intensity.blue * dot / (distance * distance));
}
