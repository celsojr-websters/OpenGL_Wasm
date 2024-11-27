cmake_minimum_required(VERSION 3.20)
project(OpenGLWASM)

# Set paths
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/third-party)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/includes)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)

# Add submodules
# add_subdirectory(${EXTERNAL_DIR}/glfw ${CMAKE_BINARY_DIR}/third-party/glfw)
# set_target_properties(glfw PROPERTIES FOLDER "Dependencies")

# GLM (header-only)
set(GLM_INCLUDE_DIR ${EXTERNAL_DIR}/glm)

# stb_image (header-only)
set(STB_INCLUDE_DIR ${EXTERNAL_DIR}/stb)

# FreeType
add_subdirectory(${EXTERNAL_DIR}/freetype ${CMAKE_BINARY_DIR}/third-party/freetype)

# Source and header files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h)
file(GLOB GLAD_FILES ${EXTERNAL_DIR}/glad/src/glad.c)

# Add executable
add_executable(OpenGLWASM ${SOURCES} ${HEADERS} ${GLAD_FILES})

# Include directories
target_include_directories(OpenGLWASM PRIVATE 
    ${INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
    ${EXTERNAL_DIR}/glad/include
    ${EXTERNAL_DIR}/freetype/include
)

# Link GLFW and FreeType libraries
target_link_libraries(OpenGLWASM glfw freetype)

# Add Emscripten-specific flags
set_target_properties(OpenGLWASM PROPERTIES 
    OUTPUT_NAME "index"
    SUFFIX ".html"
    LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1"
)

# Set the resource directory as a compile-time definition
target_compile_definitions(OpenGLWASM PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")
