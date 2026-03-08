#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "material.h"
#include "rgb_color.h"
#include "../geometries/face.h"
#include "vec3.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class OBJParser {
public:
  vector<Face> mesh;
  OBJParser(string file_path);
	vector<Material> parse_mtl(string file_path);
};

#endif
