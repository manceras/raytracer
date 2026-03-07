#include "rgb_color.h"

RGBColor::RGBColor(float r, float g, float b) : red(r), green(g), blue(b) {}

RGBColor RGBColor::operator+(const RGBColor &color) const {
  return RGBColor(color.red + red, color.green + green, color.blue + blue);
}
