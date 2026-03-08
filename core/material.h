#ifndef MATERIAL_H
#define MATERIAL_H

#include "rgb_color.h"
#include <string>

using namespace std;

struct Material {
  string name;
  float ns;
  RGBColor ka = RGBColor(1, 1, 1);
  RGBColor kd = RGBColor(1, 1, 1);
  RGBColor ks = RGBColor(1, 1, 1);
  RGBColor ke = RGBColor(1, 1, 1);
  float ni;
  float d;
  int illum;
};

#endif
