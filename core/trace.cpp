#include "trace.h"

RGBColor trace(Ray ray, vector<Light> lights, vector<Triangle> mesh,
               RGBColor color, float reflectance, int depth) {
  float distance = -1;
  Vec3 normal(0, 0, 0);
  for (const Geometry &geometry : mesh) {
    Hit hit = geometry.hit(ray);
    if (hit.t > 0 && (distance == -1 || hit.t < distance)) {
      Vec3 new_normal = geometry.normal_at(hit);
      if (new_normal * ray.direction > 0)
        new_normal = new_normal * -1;
      distance = hit.t;
      normal = new_normal;
    }
  }

  if (distance < 0)
    return RGBColor(0, 0, 0);

  Vec3 impact_point = ray.at(distance);
  RGBColor multiplier = RGBColor(0, 0, 0);
  for (const Light light : lights) {
    multiplier = multiplier + light.multiplier_for_point(normal, impact_point);
  }

  float r_brightness = multiplier.red;
  float g_brightness = multiplier.green;
  float b_brightness = multiplier.blue;

  int brightness = (r_brightness + b_brightness + g_brightness) * 10;

  if (brightness >= 10 || brightness < 0) {
    brightness = 9;
  }

  int r = r_brightness * 255;
  int g = g_brightness * 255;
  int b = b_brightness * 255;

  if (r > 255)
    r = 255;
  if (g > 255)
    g = 255;
  if (b > 255)
    b = 255;

  RGBColor difuse_color(r, g, b);

  if (depth <= 0)
    return difuse_color;

  return (1 - reflectance) * difuse_color +
         reflectance * trace(ray, lights, mesh, color, reflectance, depth - 1);
}
