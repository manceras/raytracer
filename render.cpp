#include "core/config_parser.h"
#include "core/obj_parser.h"
#include "core/rgb_color.h"
#include "core/vec3.h"
#include "core/viewport.h"
#include "geometries/geometry.h"
#include "lights/light.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

  // search for -c argument
  bool is_config_next = false;
  string config_path;
  for (int i = 0; i < argc; i++) {
    string arg = argv[i];
    if (is_config_next)
      config_path = arg;
    if (arg == "-c")
      is_config_next = true;
  }

  Config config = parse_config(config_path);

  Viewport viewport = Viewport(
      config.render.width, config.render.height, config.camera.position,
      config.camera.focal_length, config.camera.look_at);

  vector<Light> lights;
  for (const LightConfig lc : config.lights) {
    lights.push_back(Light(lc.position, lc.color));
  }

  vector<Triangle> mesh = OBJParser(config.model.file_path).mesh;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow(
      "Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      config.render.width * config.render.scale,
      config.render.height * config.render.scale, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, config.render.width, config.render.height);

  for (int row = 0; row < config.render.height; row++) {
    for (int column = 0; column < config.render.width; column++) {

      Ray ray = viewport.rayForPx(column, row);
      float distance = -1;

      Vec3 normal(0, 0, 0);

      for (const Geometry &geometry : mesh) {
        Hit hit = geometry.hit(ray);
        if (hit.t > 0 && (distance == -1 || hit.t < distance)) {
          Vec3 new_normal = geometry.normal_at(hit);
          if (new_normal * ray.direction > 0)
            new_normal = new_normal * -1;
          distance = hit.t;
          normal = new_normal;
        }
      }

      if (distance < 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, column, row);
        continue;
      }

      Vec3 impact_point = ray.at(distance);
      RGBColor multiplier = RGBColor(0, 0, 0);
      for (const Light light : lights) {
        multiplier =
            multiplier + light.multiplier_for_point(normal, impact_point);
      }

      float r_brightness = multiplier.red;
      float g_brightness = multiplier.green;
      float b_brightness = multiplier.blue;

      int brightness = (r_brightness + b_brightness + g_brightness) * 10;

      if (brightness >= 10 || brightness < 0) {
        brightness = 9;
      }

      int r = r_brightness * 255;
      int g = g_brightness * 255;
      int b = b_brightness * 255;

      if (r > 255)
        r = 255;
      if (g > 255)
        g = 255;
      if (b > 255)
        b = 255;

      SDL_SetRenderDrawColor(renderer, r, g, b, 255);
      SDL_RenderDrawPoint(renderer, column, row);
    }
  }

  SDL_RenderPresent(renderer);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
