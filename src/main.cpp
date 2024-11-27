#include <stdio.h>
#include <stdlib.h>

// Include the Emscripten library only if targeting WebAssembly
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#else
// #include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

using glm::vec3;

GLFWwindow* window;

// Handle GLFW Errors
static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

// Handle key presses
static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void force_exit() {
#ifdef __EMSCRIPTEN__
  emscripten_force_exit(EXIT_FAILURE);
#else
  exit(EXIT_FAILURE);
#endif
}

// Generate the frame data.
static void generate_frame() {
  // Clear the window with the background color
  glClear(GL_COLOR_BUFFER_BIT);
  // Flip the double buffer
  glfwSwapBuffers(window);
  // Handle any events
  glfwPollEvents();
}

static vec3 rgb(float r, float g, float b) {
  float norm = 0.004;
  return vec3(r, g, b) * norm;
}

int main() {
  // Setup the Error handler
  glfwSetErrorCallback(error_callback);

  // Start GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Error: GLFW Initialization failed.");
    force_exit();
  }

  #ifdef __APPLE__
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #else
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #endif

  // Create the display window
  window = glfwCreateWindow(640, 480, "OpenGL project", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Error: GLFW Window Creation Failed");
    glfwTerminate();
    force_exit();
  }

  // Setup the Key Press handler
  glfwSetKeyCallback(window, key_callback);

  // Select the window as the drawing destination
  glfwMakeContextCurrent(window);

  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

  // Near white background
  auto color = rgb(0.0f, 200.0f, 0.0f);
  glClearColor(color.r, color.g, color.b, 0.0f);

  // Run the loop correctly for the target environment
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(generate_frame, 0, false);
#else
  // Glad loading is required for this GL_SHADING_LANGUAGE_VERSION
  // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  //     std::cerr << "Failed to initialize GLAD" << std::endl;
  //     return -1;
  // }

  // std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  // Display the window until ESC is pressed
  while (!glfwWindowShouldClose(window)) {
    generate_frame();
  }

  // Clean up
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
#endif
}



// #include <GLFW/glfw3.h>
// #include <iostream>

// int main() {
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//     // Avoid specifying profiles for OpenGL < 3.2
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

//     GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", NULL, NULL);
//     if (!window) {
//         std::cerr << "GLFW Window Creation Failed" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);
//     const GLubyte* version = glGetString(GL_VERSION);
//     const GLubyte* renderer = glGetString(GL_RENDERER);

//     std::cout << "OpenGL Version: " << version << "\n";
//     std::cout << "Renderer: " << renderer << "\n";

//     while (!glfwWindowShouldClose(window)) {
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }


// // #include <stdio.h>
// // #include <stdlib.h>

// // #include <iostream>

// // #include <renderer.h>
// // #include <utils.h>

// // // Include the Emscripten library only if targeting WebAssembly
// // #ifdef __EMSCRIPTEN__
// // #include <emscripten/emscripten.h>
// // #define GLFW_INCLUDE_ES3
// // #endif

// // #include <glad/glad.h>
// // #include <GLFW/glfw3.h>
// // #include <glm/glm.hpp>

// // using glm::vec3;

// // GLFWwindow* window;

// // // Handle GLFW Errors
// // static void error_callback(int error, const char* description) {
// //     fprintf(stderr, "Error: %s\n", description);
// // }

// // // Handle key presses
// // static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
// //     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
// //         glfwSetWindowShouldClose(window, GLFW_TRUE);
// //     }
// // }

// // static void force_exit() {
// //     #ifdef __EMSCRIPTEN__
// //         emscripten_force_exit(EXIT_FAILURE);
// //     #else
// //         exit(EXIT_FAILURE);
// //     #endif
// // }

// // // Generate the frame data.
// // static void generate_frame() {
// //     // Clear the window with the background color
// //     glClear(GL_COLOR_BUFFER_BIT);
// //     // Flip the double buffer
// //     glfwSwapBuffers(window);
// //     // Handle any events
// //     glfwPollEvents();
// // }

// // static vec3 rgb(float r, float g, float b) {
// //     float norm = 0.004;
// //     return vec3(r, g, b) * norm;
// // }

// // int main() {
// //     // Setup the Error handler
// //     glfwSetErrorCallback(error_callback);

// //     // Start GLFW
// //     if (!glfwInit()) {
// //         fprintf(stderr, "Error: GLFW Initialization failed.");
// //         force_exit();
// //     }

// //     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// //     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
// //     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// //     #ifdef __APPLE__
// //         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// //     #endif

// //     // Create the display window
// //     window = glfwCreateWindow(640, 480, "OpenGL project", NULL, NULL);
// //     if (!window) {
// //         fprintf(stderr, "Error: GLFW Window Creation Failed");
// //         glfwTerminate();
// //         force_exit();
// //     }

// //     // Setup the Key Press handler
// //     glfwSetKeyCallback(window, key_callback);

// //     // Select the window as the drawing destination
// //     glfwMakeContextCurrent(window);

// //     // Glad loading is required for this GL_SHADING_LANGUAGE_VERSION
// //     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
// //         std::cerr << "Failed to initialize GLAD" << std::endl;
// //         return -1;
// //     }

// //     // Driver adapter information
// //     std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
// //     std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
// //     std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
// //     std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; // #include <glad/glad.h> required

// //     // Near white background
// //     auto color = rgb(100.0f, 200.0f, 0.0f);
// //     glClearColor(color.r, color.g, color.b, 0.0f);

// //     // Run the loop correctly for the target environment
// // #ifdef __EMSCRIPTEN__
// //     emscripten_set_main_loop(generate_frame, 0, false);
// // #else
// //     // Display the window until ESC is pressed
// //     while (!glfwWindowShouldClose(window)) {
// //       generate_frame();
// //     }

// //     // Clean up
// //     glfwDestroyWindow(window);
// //     glfwTerminate();
// //     exit(EXIT_SUCCESS);
// // #endif
// // }
