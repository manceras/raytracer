#include "trace.h"
#include "ray.h"
#include "rgb_color.h"
#include "vec3.h"

RGBColor trace(Ray ray, vector<Light> lights, vector<Face> mesh,
               RGBColor color, float reflectance, int depth) {
  float distance = -1;
  Vec3 normal(0, 0, 0);
  Vec3 hit_point;
	Face hit_face;
  for (const Face &face : mesh) {
    Hit hit = face.hit(ray);
    if (hit.t > 0 && (distance == -1 || hit.t < distance)) {
      Vec3 new_normal = face.normal_at(hit);
      if (new_normal * ray.direction > 0)
        new_normal = new_normal * -1;
      distance = hit.t;
      normal = new_normal;
      hit_point = ray.at(hit.t);
			hit_face = face;
    }
  }

  if (distance < 0)
    return RGBColor(0, 0, 0);

  Vec3 impact_point = ray.at(distance);
  RGBColor multiplier = RGBColor(0, 0, 0);
  for (const Light light : lights) {
    multiplier = multiplier + light.multiplier_for_point(normal, impact_point);
  }

  RGBColor difuse_color =
      RGBColor(multiplier.red, multiplier.green, multiplier.blue) * color;

  if (depth <= 0)
    return difuse_color;

  Vec3 reflected_direction =
      ray.direction - 2 * (ray.direction * normal) * normal;
  Ray reflected_ray = Ray(hit_point + normal * 0.001, reflected_direction);
  return hit_face.get_material().kd * difuse_color +
         hit_face.get_material().ks * trace(reflected_ray, lights, mesh, color, reflectance, depth - 1);
}
