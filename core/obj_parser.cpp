#include "obj_parser.h"
#include "vec3.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

OBJParser::OBJParser(string file_path, const Vec3 offset) {
  ifstream file(file_path);
  string line;

  vector<Vec3> vertices;

  while (getline(file, line)) {
    istringstream stream(line);
    string prefix;
    stream >> prefix;

    if (prefix == "v") {
      float x, y, z;
      stream >> x >> y >> z;
      vertices.push_back(Vec3(x * 0.2, y * 0.2, z * 0.2) + offset);
    }

    if (prefix == "f") {
      string v1_group, v2_group, v3_group;
      stream >> v1_group >> v2_group >> v3_group;

			int v1_index = stoi(v1_group);
			int v2_index = stoi(v2_group);
			int v3_index = stoi(v3_group);

      Vec3 v1 = vertices.at(v1_index - 1);
      Vec3 v2 = vertices.at(v2_index - 1);
      Vec3 v3 = vertices.at(v3_index - 1);

      mesh.push_back(Triangle(v1, v2, v3));
    }
  }
}
