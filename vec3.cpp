#include "vec3.h"
#include <cmath>

using namespace std;

Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3 &v) { return Vec3(x + v.x, y + v.y, z + v.z); }

Vec3 Vec3::operator-(const Vec3 &v) { return Vec3(x - v.x, y - v.y, z - v.z); }

Vec3 Vec3::operator*(float n) const { return Vec3(x * n, y * n, z * n); }

float Vec3::operator*(const Vec3 &v) { return x * v.x + y * v.y + z * v.z; }

Vec3 Vec3::normalize() {
  float mod = sqrt(x * x + y * y + z * z);
  return Vec3(x / mod, y / mod, z / mod);
}

Vec3 operator*(float n, const Vec3 &v) { return v * n; }
