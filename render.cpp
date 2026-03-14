#include "core/bvh_node.h"
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
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

void render(int initial_row, int final_row, int width, RGBColor *pixels,
            const Viewport &viewport, const vector<Light> &lights,
            const BVHNode &bvh, int objective_passes) {

  for (int _ = 0; _ < objective_passes; _++) {
    for (int row = initial_row; row < final_row; row++) {
      for (int column = 0; column < width; column++) {
        Ray ray = viewport.rayForPx(column, row);

        RGBColor color = trace(ray, lights, bvh, 3);

        float final_r = color.red * 255;
        float final_g = color.green * 255;
        float final_b = color.blue * 255;

        if (final_r > 255)
          final_r = 255;
        if (final_g > 255)
          final_g = 255;
        if (final_b > 255)
          final_b = 255;

        RGBColor final_color(final_r, final_g, final_b);
        pixels[row * width + column] =
            (final_color + pixels[row * width + column]);
      }
    }
  }
}

int main(int argc, char *argv[]) {

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

  BVHNode bvh = BVHNode(object.mesh);

  const int height = config.render.height;
  const int width = config.render.width;
  RGBColor *pixels = new RGBColor[height * width];

  const int n_cores = std::thread::hardware_concurrency();
  vector<thread> threads;

  int rows_per_group = height / n_cores;

  auto start = chrono::high_resolution_clock::now();

  int objective_passes = 30;

  for (int group = 0; group < n_cores; group++) {
    int last_row;
    if (group < n_cores - 1)
      last_row = (group + 1) * rows_per_group;
    else
      last_row = height;
    threads.emplace_back(render, group * rows_per_group, last_row, width,
                         pixels, std::ref(viewport), std::ref(lights),
                         std::ref(bvh), objective_passes);
  }

  for (thread &t : threads)
    t.join();

  for (int i = 0; i < width * height; i++) {
    RGBColor avarage = pixels[i] * (1.0 / objective_passes);
		pixels[i] = avarage;
  }

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  printf("Render time: %ldms\n", duration.count());

  for (int i = 0; i < width * height; i++) {
    RGBColor px = pixels[i];
    int row = (int)i / width;
    int column = i % width;

    SDL_SetRenderDrawColor(renderer, px.red, px.green, px.blue, 255);
    SDL_RenderDrawPoint(renderer, column, row);
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

  delete[] pixels;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
