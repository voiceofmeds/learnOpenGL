#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "utils.h"

typedef struct {
  GLFWwindow *window;
  int width;
  int height;
  char *title;
  GLFWmonitor *monitor;
  GLFWwindow *share;
} state_t;

void glfw_error_callback(int error, const char *description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

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
  state_t state = {
    .window = NULL,
    .width = 800,
    .height = 600,
    .title = "Cube",
    .monitor = NULL,
    .share = NULL,
  };

  // initialize everything in order
  init_error();
  init_glfw();

  init_window(&state);
  init_glad();
  init_viewport(&state);
  init_input(&state);
  init_loop(&state);

  // terminate GLFW (clean/delete all of GLFW resources that were allocated)
  // then exit the program
  glfwTerminate();
  return 0;
}

void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "[%d]GLFW Error: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void init_glfw(void) {
  // if initializing glfw fails exit the program
  if (!glfwInit()) {
    glfwTerminate();
    panic("Failed to initialize GLFW", -1);
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
    state->height == 0 ? 600 : state->height,
    state->title == NULL ? "Default" : state->title,
    state->monitor == NULL ? NULL : state->monitor,
    state->share == NULL ? NULL : state->share
  );

  // if creating the window fails exit the program
  if (window == NULL) {
    glfwTerminate();
    panic("Failed to initialize GLFW", -2);
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
    panic("Failed to initialize GLAD", -3);
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
