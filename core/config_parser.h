#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "rgb_color.h"
#include "vec3.h"
#include <string>
#include <vector>

using namespace std;

struct Camera {
	Vec3 position;
	Vec3 look_at;
	float focal_length;
};

struct Render {
	int width;
	int height;
	float scale;
};

struct LightConfig {
	Vec3 position;
	RGBColor color;
};

struct Model {
	string file_path;
	RGBColor color;
};

struct Config {
	Camera camera;
	Render render;
	vector<LightConfig> lights;
	Model model;
};

Config parse_config(string config_path);

#endif
