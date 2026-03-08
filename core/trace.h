#ifndef TRACE_H
#define TRACE_H

#include "../geometries/triangle.h"
#include "../lights/light.h"
#include "rgb_color.h"
#include <vector>

using namespace std;

RGBColor trace(Ray ray, vector<Light> lights, vector<Triangle> mesh,
               RGBColor color, float reflectancy, int depth);

#endif
