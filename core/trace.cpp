#include "trace.h"
#include "../utils/random_dir.h"
#include "bvh_node.h"
#include "ray.h"
#include "rgb_color.h"
#include "vec3.h"

RGBColor trace(Ray ray, vector<Light> lights, const BVHNode &bvh, int depth) {

  optional<HitFace> hit_face_opt = bvh.hit_face(ray);

  if (!hit_face_opt)
    return RGBColor(0, 0, 0);

  HitFace hit_face = hit_face_opt.value();
  float distance = hit_face.hit.t;
  Vec3 normal = hit_face.face.normal_at(hit_face.hit);
  Vec3 hit_point = ray.at(distance);
  Vec3 impact_point = ray.at(distance);

  if (normal * ray.direction < 0)
    normal = normal * -1;

  RGBColor multiplier = RGBColor(0, 0, 0);
  for (const Light light : lights) {
    multiplier = multiplier + light.multiplier_for_point(normal, impact_point);
  }

  if (depth <= 0) {
    return multiplier;
  }

  Vec3 difused_direction = random_direction();

  if (difused_direction * normal < 0)
    difused_direction = -1 * difused_direction;

  Ray difused_ray = Ray(hit_point + normal * 0.001, difused_direction);

  Vec3 reflected_direction =
      ray.direction - 2 * (ray.direction * normal) * normal;
  Ray reflected_ray = Ray(hit_point + normal * 0.001, reflected_direction);

  return hit_face.face.get_material().kd * trace(difused_ray, lights, bvh, depth -1) + multiplier +
         hit_face.face.get_material().ks *
             trace(reflected_ray, lights, bvh, depth - 1);
}
