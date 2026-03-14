CXX = g++
CXXFLAGS = -O2 -I tomlplusplus/include
SDL_FLAGS = $(shell sdl2-config --cflags --libs)

CORE = core/vec3.cpp core/ray.cpp core/viewport.cpp core/rgb_color.cpp core/obj_parser.cpp core/vertex.cpp core/config_parser.cpp core/trace.cpp core/aabb.cpp core/bvh_node.cpp
UTILS = utils/random_dir.cpp
GEOMETRIES = geometries/face.cpp
LIGHTS = lights/light.cpp

all: out

out: render.cpp $(CORE) $(GEOMETRIES) $(LIGHTS) $(UTILS)
	$(CXX) $(CXXFLAGS) -o out render.cpp $(CORE) $(GEOMETRIES) $(LIGHTS) $(UTILS) $(SDL_FLAGS)

clean:
	rm -f out

.PHONY: all clean
