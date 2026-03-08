#ifndef  OBJ_PARSER_H
#define OBJ_PARSER_H

#include "vec3.h"
#include "../geometries/triangle.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class OBJParser {
public:
	vector<Triangle> mesh;
	OBJParser(string file_path, const Vec3 offset = Vec3(0, 0, 0));
};

#endif
