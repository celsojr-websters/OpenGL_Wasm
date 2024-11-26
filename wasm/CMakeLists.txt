# WASM build configuration
cmake_minimum_required(VERSION 3.20)
project(OpenGLWASM)

# FetchContent for dependencies
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# stb_image
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# FreeType
FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
    GIT_TAG VER-2-13-0
)
FetchContent_MakeAvailable(freetype)

# GLOB for sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h)

# Add executable
add_executable(OpenGLWASM ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(OpenGLWASM PRIVATE ${INCLUDE_DIR} ${stb_SOURCE_DIR})

# Link libraries
target_link_libraries(OpenGLWASM glfw glm freetype)

# Resources
target_compile_definitions(OpenGLWASM PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")

# Add Emscripten-specific flags
set_target_properties(OpenGLWASM PROPERTIES 
    OUTPUT_NAME "index"
    SUFFIX ".html"
    LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1")
em_link_js_library(wasm ${libraryJsFiles})
