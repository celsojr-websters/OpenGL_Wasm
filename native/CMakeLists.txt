cmake_minimum_required(VERSION 3.20)
project(OpenGLNative)

# Get variables from the parent scope
set(SRC_DIR ${SRC_DIR})
set(INCLUDE_DIR ${INCLUDE_DIR})
set(RESOURCES_DIR ${RESOURCES_DIR})
set(EXTERNAL_DIR ${EXTERNAL_DIR})

# Add submodules
add_subdirectory(${EXTERNAL_DIR}/glfw ${CMAKE_BINARY_DIR}/third-party/glfw)
set_target_properties(glfw PROPERTIES FOLDER "Dependencies")

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
add_executable(OpenGLNative ${SOURCES} ${HEADERS} ${GLAD_FILES})

# Include directories
target_include_directories(OpenGLNative PRIVATE 
    ${INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
    ${EXTERNAL_DIR}/glad/include
    ${EXTERNAL_DIR}/freetype/include
)

# Link OpenGL and other libraries
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLNative
    OpenGL::GL
    glfw
    freetype
)

# Set the resource directory as a compile-time definition
target_compile_definitions(OpenGLNative PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")
