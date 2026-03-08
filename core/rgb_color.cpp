#include "rgb_color.h"

RGBColor::RGBColor(float r, float g, float b) : red(r), green(g), blue(b) {}
RGBColor::RGBColor() : red(0), green(0), blue(0) {}

RGBColor RGBColor::operator+(const RGBColor &color) const {
  return RGBColor(color.red + red, color.green + green, color.blue + blue);
}

RGBColor RGBColor::operator*(const RGBColor &color) const {
  return RGBColor(color.red * red, color.green * green, color.blue * blue);
}

RGBColor RGBColor::operator*(float n) const {
  return RGBColor(n * red, n * green, n * blue);
}

RGBColor operator*(float n, const RGBColor &c) {
  return RGBColor(c.red * n, c.green * n, c.blue * n);
}
