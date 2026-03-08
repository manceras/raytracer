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
  vector<Material> materials;
  Material current_material;

  while (getline(file, line)) {
    istringstream stream(line);
    string prefix;
    stream >> prefix;

    if (prefix == "mtllib") {
      string material_file_path;
      stream >> material_file_path;
			string dir = file_path.substr(0, file_path.find_last_of('/') + 1);
      materials = parse_mtl(dir + material_file_path);
    }

    if (prefix == "usemtl") {
      string material_name;
      stream >> material_name;
      for (const Material &material : materials) {
        if (material.name == material_name)
          current_material = material;
      }
    }

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
        mesh.push_back(Face(Vertex(v1, n1), Vertex(v3, n3), Vertex(v4, n4),
                            current_material));
      }

      mesh.push_back(Face(Vertex(v1, n1), Vertex(v2, n2), Vertex(v3, n3),
                          current_material));
    }
  }
}

vector<Material> OBJParser::parse_mtl(string file_path) {
  ifstream file(file_path);
  string line;

  vector<Material> materials;
  Material current_mtl;

  while (getline(file, line)) {
    istringstream stream(line);
    string prefix;
    stream >> prefix;

    if (prefix == "newmtl") {
      if (!current_mtl.name.empty()) {
        materials.push_back(current_mtl);
        current_mtl = {};
      }
      stream >> current_mtl.name;
    }

    if (prefix == "Kd") {
      float r, g, b;
      stream >> r >> g >> b;
      current_mtl.kd = RGBColor(r, g, b);
    }

    if (prefix == "Ks") {
      float r, g, b;
      stream >> r >> g >> b;
      current_mtl.ks = RGBColor(r, g, b);
    }
  }

  materials.push_back(current_mtl);
  return materials;
}
