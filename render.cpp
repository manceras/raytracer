#include "core/config_parser.h"
#include "core/obj_parser.h"
#include "core/rgb_color.h"
#include "core/trace.h"
#include "core/vec3.h"
#include "core/viewport.h"
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

  OBJParser object = OBJParser(config.model.file_path);

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

      RGBColor color =
          trace(ray, lights, object, 5);

			float final_r = color.red * 255;
			float final_g = color.green * 255;
			float final_b = color.blue * 255;

			if (final_r > 255) final_r = 255;
			if (final_g > 255) final_g = 255;
			if (final_b > 255) final_b = 255;

			RGBColor final_color(final_r, final_g, final_b);

      SDL_SetRenderDrawColor(renderer, final_color.red, final_color.green,
                             final_color.blue, 255);
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
