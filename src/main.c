#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"

// use snake_case for own functions
// camelCase are glfw/glad functions
// to know each one from the other clearly

typedef struct {
  GLFWwindow *window;
  int width;
  int height;
  char *title;
  GLFWmonitor *monitor;
  GLFWwindow *share;
} state_t;

// "We register the callback functions after we've created the window
// and before the render loop is initiated"
// 
// Maybe the error callback doesn't count?
void glfw_error_callback(int error, const char *description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void init_glfw(void);
void init_window(state_t *state);
void init_glad(void);

// these set callbacks
void init_error(void);
void init_viewport(state_t *state);
void init_input(state_t *state);

void render(void);
void init_loop(state_t *state);

int main(void) {
  // zero-initialize the state
  state_t state = {
    .width = 800,
    .height = 600,
    .title = "Cube"
  };

  // initialize everything in order
  init_glfw();
  init_window(&state);
  init_glad();
  init_error();
  init_viewport(&state);
  init_input(&state);
  init_loop(&state);

  // terminate GLFW (clean/delete all of GLFW resources that were allocated)
  // then exit the program
  glfwTerminate();
  return 0;
}

void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { 
  if (0 <= key && key < key_handler_size && key_handlers[key]) key_handlers[key](window);
}

void init_glfw(void) {
  // if initializing glfw fails exit the program
  if (!glfwInit()) {
    glfwTerminate();
    exit(-2);
  };

  // set up the opengl version to 3.3 and use the core profile
  // without this the program might not run on some systems
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void init_window(state_t *state) {
  // we create the window
  GLFWwindow *window = glfwCreateWindow(
    state->width == 0 ? 800 : state->width,
    state->height == 0 ? 600: state->height,
    state->title == NULL ? "Default" : state->title,
    state->monitor,
    state->share
  );
  // if creating the window fails exit the program
  if (window == NULL) {
    glfwTerminate();
    exit(-2);
  };
  // make state->window point to this new window
  // then make the current context the newly made window
  state->window = window;
  glfwMakeContextCurrent(state->window);
}

void init_glad(void) {
  // if initializing glad fails exit the program
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    exit(-3);
  }
}

void init_error(void) {
  glfwSetErrorCallback(glfw_error_callback);
}

void init_viewport(state_t *state) {
  glfwSetFramebufferSizeCallback(state->window, framebuffer_size_callback);
}

void init_input(state_t *state) {
  glfwSetKeyCallback(state->window, process_input_callback);
}

void render(void) {
  // Whenever we call glClear and clear the color buffer,
  // the entire color buffer will be filled with the color as configured by glClearColor
  //
  // glClearColor is a state-setting function
  // glClear is a state-using function
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void init_loop(state_t *state) {
  while (!glfwWindowShouldClose(state->window)) {
    // checks if any events are triggered
    // updates the window state
    // and calls corresponding functions (callbacks, etc..)
    glfwPollEvents();

    render();

    // swaps the back buffer (the buffer where everything is drawn to)
    // to the front buffer
    glfwSwapBuffers(state->window);
  }
}
