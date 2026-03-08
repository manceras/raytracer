#include "obj_parser.h"
#include "vec3.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

struct VertexValues {
  int normal;
  int vertex;
  int texture;
};

VertexValues vertexValues(string group) {
  int normal, vertex, texture;
  replace(group.begin(), group.end(), '/', ' ');
  istringstream stream(group);
  stream >> vertex >> texture >> normal;
  return {normal, vertex, texture};
}

OBJParser::OBJParser(string file_path) {
  ifstream file(file_path);
  string line;

  vector<Vec3> vertices;
  vector<Vec3> normals;

  while (getline(file, line)) {
    istringstream stream(line);
    string prefix;
    stream >> prefix;

    if (prefix == "v") {
      float x, y, z;
      stream >> x >> y >> z;
      vertices.push_back(Vec3(x, y, z));
    }

    if (prefix == "vn") {
      float x, y, z;
      stream >> x >> y >> z;
      normals.push_back(Vec3(x, y, z));
    }

    if (prefix == "f") {
      string v1_group, v2_group, v3_group, v4_group;
      stream >> v1_group >> v2_group >> v3_group >> v4_group;

      VertexValues v1_values = vertexValues(v1_group);
      VertexValues v2_values = vertexValues(v2_group);
      VertexValues v3_values = vertexValues(v3_group);

      Vec3 v1 = vertices.at(v1_values.vertex - 1);
      Vec3 v2 = vertices.at(v2_values.vertex - 1);
      Vec3 v3 = vertices.at(v3_values.vertex - 1);

      Vec3 n1 = normals.at(v1_values.normal - 1);
      Vec3 n2 = normals.at(v2_values.normal - 1);
      Vec3 n3 = normals.at(v3_values.normal - 1);

      if (!v4_group.empty()) {
        VertexValues v4_values = vertexValues(v4_group);
        Vec3 v4 = vertices.at(v4_values.vertex - 1);
        Vec3 n4 = normals.at(v4_values.normal - 1);
        mesh.push_back(
            Triangle(Vertex(v1, n1), Vertex(v3, n3), Vertex(v4, n4)));
      }

      mesh.push_back(Triangle(Vertex(v1, n1), Vertex(v2, n2), Vertex(v3, n3)));
    }
  }
}
