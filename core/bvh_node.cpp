#include "bvh_node.h"
#include "aabb.h"
#include "vec3.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <optional>
#include <utility>

BVHNode::BVHNode(AABB aabb, unique_ptr<BVHNode> left, unique_ptr<BVHNode> right)
    : aabb(aabb), left(std::move(left)), right(std::move(right)),
      face(std::nullopt) {};

BVHNode::BVHNode(AABB aabb, Face face) : aabb(aabb), face(face) {}

BVHNode::BVHNode(vector<Face> mesh) {
  if (mesh.size() == 1) {
    Face face = mesh.at(0);
    Vec3 v1 = face.get_v1().position;
    Vec3 v2 = face.get_v2().position;
    Vec3 v3 = face.get_v3().position;

    float max_x = std::max({v1.x, v2.x, v3.x});
    float max_y = std::max({v1.y, v2.y, v3.y});
    float max_z = std::max({v1.z, v2.z, v3.z});

    float min_x = std::min({v1.x, v2.x, v3.x});
    float min_y = std::min({v1.y, v2.y, v3.y});
    float min_z = std::min({v1.z, v2.z, v3.z});

    this->aabb = AABB(Vec3(min_x, min_y, min_z), Vec3(max_x, max_y, max_z));
    this->face = face;
		return;
  }

  float max_x = -INFINITY;
  float max_y = -INFINITY;
  float max_z = -INFINITY;
  float min_x = INFINITY;
  float min_y = INFINITY;
  float min_z = INFINITY;

  for (const Face &face : mesh) {
    Vec3 v1 = face.get_v1().position;
    Vec3 v2 = face.get_v2().position;
    Vec3 v3 = face.get_v3().position;

    float new_max_x = std::max({v1.x, v2.x, v3.x});
    float new_max_y = std::max({v1.y, v2.y, v3.y});
    float new_max_z = std::max({v1.z, v2.z, v3.z});

    float new_min_x = std::min({v1.x, v2.x, v3.x});
    float new_min_y = std::min({v1.y, v2.y, v3.y});
    float new_min_z = std::min({v1.z, v2.z, v3.z});

    if (new_max_x > max_x)
      max_x = new_max_x;
    if (new_max_y > max_y)
      max_y = new_max_y;
    if (new_max_z > max_z)
      max_z = new_max_z;

    if (new_min_x < min_x)
      min_x = new_min_x;
    if (new_min_y < min_y)
      min_y = new_min_y;
    if (new_min_z < min_z)
      min_z = new_min_z;
  }

  float x_lenght = max_x - min_x;
  float y_lenght = max_y - min_y;
  float z_lenght = max_z - min_z;

  vector<Face> ordered = mesh;

  if (x_lenght >= y_lenght && x_lenght >= z_lenght) {
    std::sort(ordered.begin(), ordered.end(), [](const Face &a, const Face &b) {
      return a.centroid().x < b.centroid().x;
    });
  } else if (y_lenght >= x_lenght && y_lenght >= z_lenght) {
    std::sort(ordered.begin(), ordered.end(), [](const Face &a, const Face &b) {
      return a.centroid().y < b.centroid().y;
    });
  } else {
    std::sort(ordered.begin(), ordered.end(), [](const Face &a, const Face &b) {
      return a.centroid().z < b.centroid().z;
    });
  }

	vector<Face> left_half(ordered.begin(), ordered.begin() + ordered.size() / 2);
	vector<Face> right_half(ordered.begin() + ordered.size() / 2, ordered.end());

	this->aabb = AABB(Vec3(min_x, min_y, min_z), Vec3(max_x, max_y, max_z));
	this->left = std::make_unique<BVHNode>(left_half);
	this->right = std::make_unique<BVHNode>(right_half);
}

optional<HitFace> BVHNode::hit_face(const Ray &ray) const {
	if (!aabb.hit(ray)) return nullopt;

	if (!this->left && !this->right) {
		Hit hit = face->hit(ray);
		if (hit.t <= 0) return nullopt;
		return HitFace{face.value(), hit};
	}

	optional<HitFace> left_hit = this->left->hit_face(ray);
	optional<HitFace> right_hit = this->right->hit_face(ray);

	if (!left_hit && !right_hit) return nullopt;
	if (!left_hit && right_hit) return right_hit;
	if (left_hit && !right_hit) return left_hit;
	if (left_hit->hit.t <= right_hit->hit.t) return left_hit;
	return right_hit;
}
