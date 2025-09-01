#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "input.h"

void (*key_handlers[]) (GLFWwindow *window) = {
  [GLFW_KEY_ESCAPE] = terminate_glfw,
};

void terminate_glfw(GLFWwindow *window) {
  glfwSetWindowShouldClose(window, true);
}
