cmake_minimum_required(VERSION 3.20)
project(OpenGLProject)

# Set default C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Avoid extra unnecessary third-party builds
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Compiler Flags for Debug Mode
set(CMAKE_BUILD_TYPE Debug)

if (MSVC)
    # /Zi: Generates debugging information.
    # /Od: Disables optimizations.
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od")
else()
    # -g: Generates debugging information.
    # -O0: Disables optimizations (important for accurate debugging).
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()

# Options for building
option(BUILD_WASM "Build for WebAssembly" OFF)

# Paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Add subdirectories
if (BUILD_WASM)
    message(STATUS "WebAssembly build enabled")
    message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")
    add_subdirectory(wasm)
else()
    message(STATUS "Native build enabled")
    add_subdirectory(native)
endif()
