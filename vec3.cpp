#include <cmath>

using namespace std;

class Vec3 {
public:
	float x, y, z;

  Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vec3 operator+(const Vec3 &v) { return Vec3(x + v.x, y + v.y, z + v.z); }

  Vec3 operator-(const Vec3 &v) { return Vec3(x - v.x, y - v.y, z - v.z); }

  Vec3 operator*(float n) { return Vec3(x * n, y * n, z * n); }

  float operator*(const Vec3 &v) { return x * v.x + y * v.y + z * v.z; }

  Vec3 normalize() {
    float mod = sqrt(x*x + y*y + z*z);
    return Vec3(x / mod, y / mod, z / mod);
  }
};
