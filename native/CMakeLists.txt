# Native build configuration
cmake_minimum_required(VERSION 3.20)
project(OpenGLNative)

# FetchContent for dependencies
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(glm)

# stb_image
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(stb)

# FreeType
FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
    GIT_TAG VER-2-13-0
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(freetype)

# GLOB for sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h)

# Add executable
add_executable(OpenGLNative ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(OpenGLNative PRIVATE ${INCLUDE_DIR} ${stb_SOURCE_DIR})

# Is the OpenGL available in the Operating System?
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(OpenGLNative OpenGL::GL glfw glm freetype)

# Resources
target_compile_definitions(OpenGLNative PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")
