#ifndef TRACE_H
#define TRACE_H

#include "../geometries/face.h"
#include "../lights/light.h"
#include "bvh_node.h"
#include "obj_parser.h"
#include "rgb_color.h"
#include <vector>

using namespace std;

RGBColor trace(Ray ray, vector<Light> lights, const BVHNode &bvh, int depth);

#endif
