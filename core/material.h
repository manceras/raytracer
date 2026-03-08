#ifndef MATERIAL_H
#define MATERIAL_H

#include "rgb_color.h"
#include <string>

using namespace std;

struct Material {
	string name;
  float ns;
  RGBColor ka;
  RGBColor kd;
  RGBColor ks;
  RGBColor ke;
  float ni;
  float d;
	int illum; 
};

#endif
