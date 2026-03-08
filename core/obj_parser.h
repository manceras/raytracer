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
private:
	Vec3 max_vertex;
	Vec3 min_vertex;
public:
  vector<Face> mesh;
	vector<Material> parse_mtl(string file_path);

  OBJParser(string file_path);
	Vec3 get_max_vertex() const;
	Vec3 get_min_vertex() const;
};

#endif
