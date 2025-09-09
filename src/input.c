#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "input.h"

static void terminate_glfw(GLFWwindow *window);

static void (*key_handlers[]) (GLFWwindow *window) = {
  [GLFW_KEY_ESCAPE] = terminate_glfw,
};

static unsigned int key_handler_size = sizeof(key_handlers) / sizeof(key_handlers[0]);

void process_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { 
  if (0 <= key && key < key_handler_size && key_handlers[key]) key_handlers[key](window);
}

static void terminate_glfw(GLFWwindow *window) {
  glfwSetWindowShouldClose(window, true);
}
