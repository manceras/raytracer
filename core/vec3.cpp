#include "vec3.h"
#include <cmath>

using namespace std;

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3 &v) const {
  return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3 &v) const {
  return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(float n) const { return Vec3(x * n, y * n, z * n); }

float Vec3::operator*(const Vec3 &v) const {
  return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::normalize() const {
  float mod = modulus();
  return Vec3(x / mod, y / mod, z / mod);
}

float Vec3::modulus() const { return sqrt(x * x + y * y + z * z); }

Vec3 Vec3::cross(const Vec3 &v) const {
  float x = this->y * v.z - this->z * v.y;
  float y = this->z * v.x - this->x * v.z;
  float z = this->x * v.y - this->y * v.x;
  return Vec3(x, y, z);
}

Vec3 operator*(float n, const Vec3 &v) { return v * n; }
