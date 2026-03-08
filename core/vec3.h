#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
  float x, y, z;

  Vec3(float x, float y, float z);
  Vec3 operator+(const Vec3 &v) const;
  Vec3 operator-(const Vec3 &v) const;
  Vec3 operator*(float n) const;
  float operator*(const Vec3 &v) const;
  Vec3 normalize() const;
	float modulus() const;
	Vec3 cross(const Vec3 &v) const;
};

Vec3 operator*(float n, const Vec3 &v);

#endif
