# OpenGLProject

A cross-platform OpenGL project supporting native builds on Windows, Linux, and macOS, as well as WebAssembly (WASM) builds for the web.

## Project Structure

```sh
project/
├── includes/
# Header files (e.g., renderer.h, utils.h)
├── src/ # Source files (e.g., main.cpp, renderer.cpp)
├── resources/ # Shaders, textures, and other assets
├── native/ # CMake configurations for native builds
├── wasm/ # CMake configurations for WASM builds
├── .vscode/ # VSCode configuration files
├── Makefile # Makefile for simplified building
└── README.md # This file
```

## Prerequisites

- CMake 3.20 or later
- A C++17-compatible compiler (e.g., GCC, Clang, or MSVC)
- Emscripten (for WASM builds)
- Git (for fetching dependencies)

## Building

### Native Build

```sh
make native
```
This will create a native executable in `build/native`.

### WASM Build
```sh
make wasm
```
This will create a native executable in `build/wasm`.

## Resources Directory

All shaders, textures, and other assets are located in the `resources` folder. Access this folder using the `RESOURCES_DIR` macro defined in the build configuration.

Example:
```sh
std::string vertexShaderPath = std::string(RESOURCES_DIR) + "/shaders/vertex_shader.glsl";
```

### Task list
- [x] Wasm build not tested yet
- [x] Better code example for testing
- [ ] Formatting rules
- [ ] (WIP) Third-party libraries as git sub modules
- [x] Windows build support test
- [ ] Linux support test
- [x] macOS build support test
- [ ] Breakpoint not being hit in the debug mode from VS Code

```sh
git clone --recurse-submodules <repository-url>
git submodule update --init --recursive
```