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

int main() {
  int height = 300;
  int width = 300;

  Viewport viewport = Viewport(width, height, Vec3(0, -2, 1), 1, Vec3(0, 0, 0));

  Vec3 offset = Vec3(0, 0, 0.5);

  Light light1 = Light(Vec3(0, 0, 0.1), RGBColor(1, 0, 0));
  Light light2 = Light(Vec3(0, 1, 1), RGBColor(0, 1, 0));
  Light light3 = Light(Vec3(0, -2, 0), RGBColor(0, 0, 1));

  vector mesh = OBJParser("./3d_files/Suzane.obj").mesh;

  const int lights_length = 3;
  Light *lights[lights_length] = {&light1, &light2, &light3};

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window =
      SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, width, height);

  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {

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
      for (int i = 0; i < lights_length; i++) {
        Light *light = lights[i];
        multiplier =
            multiplier + light->multiplier_for_point(normal, impact_point);
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
