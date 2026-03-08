# Raytracer

A raytracer built from scratch in C++ as a learning project. No graphics engine, no shortcuts — just math and pixels.

![Suzanne render](screenshot.png)

## Features

- Ray-triangle intersection using the Möller-Trumbore algorithm
- Lambertian (diffuse) shading with inverse square law falloff
- Smooth shading via vertex normal interpolation
- Reflections with configurable recursion depth
- Per-face materials via MTL file parsing (Kd, Ks)
- Colored point lights (as many as you want)
- OBJ file loading (triangles and quads)
- Configurable camera with position, look-at and focal length
- SDL2 graphical output with resolution scaling
- TOML-based scene configuration

## Dependencies

- g++
- SDL2 (`sdl2-config` must be available)
- [toml++](https://github.com/marax27/tomlplusplus) (included in the repo)

### Installing SDL2

**Fedora:**
```
sudo dnf install SDL2-devel
```

**Ubuntu/Debian:**
```
sudo apt install libsdl2-dev
```

## Build

```
make
```

## Usage

```
./out -c config.toml
```

### Scene configuration

Scenes are defined in TOML files:

```toml
[camera]
position = [1, 0.8, 2]
look_at = [0, 0.3, 0]
focal_length = 1

[render]
width = 800
height = 600
scale = 1

[[lights]]
position = [2, 2, 3]
color = [20, 18, 15]

[[lights]]
position = [-2, 2, 1]
color = [6, 8, 16]

[[lights]]
position = [0, 3, -1]
color = [8, 6, 12]

[model]
file = "./3d_files/Suzanne.obj"
```
