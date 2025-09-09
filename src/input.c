#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "input.h"

void (*key_handlers[]) (GLFWwindow *window) = {
  [GLFW_KEY_ESCAPE] = terminate_glfw,
};

unsigned int key_handler_size = sizeof(key_handlers) / sizeof(key_handlers[0]);

void terminate_glfw(GLFWwindow *window) {
  glfwSetWindowShouldClose(window, true);
}
