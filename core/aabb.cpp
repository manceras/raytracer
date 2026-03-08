
#include "aabb.h"
#include <algorithm>

AABB::AABB(Vec3 min, Vec3 max): min(min), max(max) {}
AABB::AABB(): min(Vec3(0, 0, 0)), max(Vec3(0, 0, 0)) {}

bool AABB::hit(const Ray &ray) const {
	float min_tx = (min.x - ray.point.x) / ray.direction.x;
	float max_tx = (max.x - ray.point.x) / ray.direction.x;
	float entry_tx = std::min(min_tx, max_tx);
	float exit_tx = std::max(min_tx, max_tx);

	float max_ty = (max.y - ray.point.y) / ray.direction.y;
	float min_ty = (min.y - ray.point.y) / ray.direction.y;
	float entry_ty = std::min(min_ty, max_ty);
	float exit_ty = std::max(min_ty, max_ty);

	float min_tz = (min.z - ray.point.z) / ray.direction.z;
	float max_tz = (max.z - ray.point.z) / ray.direction.z;
	float entry_tz = std::min(min_tz, max_tz);
	float exit_tz = std::max(min_tz, max_tz);

	float entry = std::max({entry_tx, entry_ty, entry_tz});
	float exit = std::min({exit_tx, exit_ty, exit_tz});

	if (exit < 0) return false;

	return entry <= exit;
}
