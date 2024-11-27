cmake_minimum_required(VERSION 3.20)
project(OpenGLProject)

# Set default C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Debug Mode Flags
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

# Disable unnecessary GLFW features
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Enable or disable shared libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Options for building
option(BUILD_WASM "Build for WebAssembly" OFF)

# Paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/third-party)

# Pass common variables to subdirectories
set(COMMON_CMAKE_ARGS 
    -DSRC_DIR=${SRC_DIR}
    -DINCLUDE_DIR=${INCLUDE_DIR}
    -DRESOURCES_DIR=${RESOURCES_DIR}
    -DEXTERNAL_DIR=${EXTERNAL_DIR}
)

# Conditional builds
if (BUILD_WASM)
    message(STATUS "WebAssembly build enabled")
    message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")
    add_subdirectory(wasm)
else()
    message(STATUS "Native build enabled")
    add_subdirectory(native)
endif()
