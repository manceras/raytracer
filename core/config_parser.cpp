#include "config_parser.h"
#include "../tomlplusplus/toml.hpp"
#include "rgb_color.h"
#include "vec3.h"
#include <iostream>
#include <optional>

using namespace std;

Vec3 parse_vec3(toml::node_view<toml::node> node, const string &name) {
  optional<float> x = node[0].value<float>();
  optional<float> y = node[1].value<float>();
  optional<float> z = node[2].value<float>();

  if (!x || !y || !z) {
    cerr << "Missing or invalid: " << name << endl;
    exit(1);
  }

  return Vec3(*x, *y, *z);
}

RGBColor parse_rgb_color(toml::node_view<toml::node> node, const string &name) {
  Vec3 vec = parse_vec3(node, name);
  return RGBColor(vec.x, vec.y, vec.z);
}

Config parse_config(string config_path) {
  toml::table tbl;

  try {
    tbl = toml::parse_file(config_path);
  } catch (const toml::parse_error &err) {
    cerr << "Parsing failed:\n" << err << "\n";
    exit(1);
  }

  Config config;

  config.camera.position =
      parse_vec3(tbl["camera"]["position"], "camera.position");
  config.camera.look_at =
      parse_vec3(tbl["camera"]["look_at"], "camera.look_at");
  config.camera.focal_length = tbl["camera"]["focal_length"].value_or(1.0f);

  config.render.width = tbl["render"]["width"].value_or(300);
  config.render.height = tbl["render"]["height"].value_or(300);
  config.render.scale = tbl["render"]["scale"].value_or(1.0f);

  config.model.file_path = tbl["model"]["file"].value_or("model.obj"s);


  if (auto lights = tbl["lights"].as_array()) {
    for (auto &light : *lights) {
      auto *t = light.as_table();
      LightConfig lc;
      lc.position = parse_vec3((*t)["position"], "lights.position");
      lc.color = parse_rgb_color((*t)["color"], "lights.color");
      config.lights.push_back(lc);
    }
  }

  return config;
}
