#include "obj_parser.h"
#include "vec3.h"
#include <sstream>
#include <string>
#include <vector>

OBJParser::OBJParser(string file_path) {
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
      vertices.push_back(Vec3(x, y, z));
    }

    if (prefix == "f") {
      int v1_index, v2_index, v3_index;
      stream >> v1_index >> v2_index >> v3_index;

      Vec3 v1 = vertices.at(v1_index - 1);
      Vec3 v2 = vertices.at(v2_index - 1);
      Vec3 v3 = vertices.at(v3_index - 1);

      mesh.push_back(Triangle(v1, v2, v3));
    }
  }
}
