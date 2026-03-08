#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "../geometries/face.h"
#include "aabb.h"
#include <memory>
#include <optional>
#include <vector>

struct HitFace {
	Face face;
	Hit hit;
};

class BVHNode {
private:
  AABB aabb;
  std::unique_ptr<BVHNode> left;
  std::unique_ptr<BVHNode> right;
  optional<Face> face;

public:
  BVHNode(AABB aabb, Face face);
  BVHNode(AABB aabb, unique_ptr<BVHNode> left, unique_ptr<BVHNode> right);
  BVHNode(vector<Face> mesh);
	optional<HitFace> hit_face(const Ray &ray) const;
};

#endif
