#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// use snake_case for our own functions
// camelCase are glfw/glad functions
// this is to easily know each one from another

typedef struct {
  GLFWwindow *window;
  unsigned int width;
  unsigned int height;
  char *title;
  GLFWmonitor *monitor;
  GLFWwindow *share;
} state_t;

void glfw_error_callback(const int error, const char *description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void init_error(void);
void init_glfw(void);
void init_window(state_t *state);
void init_glad(void);
void init_render(state_t *state);

void loop(state_t *state);

int main(void) {
  // zero-initialize the state
  state_t state = {
    .width = 800,
    .height = 600,
    .title = "Cube"
  };

  init_error();
  init_glfw();
  init_window(&state);
  init_glad();
  init_render(&state);
  loop(&state);

  return 0;
}

void glfw_error_callback(const int error, const char *description) {
  fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void init_error(void) {
  glfwSetErrorCallback(glfw_error_callback);
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

void init_render(state_t *state) {
  glViewport(0, 0, state->width, state->height);

  glfwSetFramebufferSizeCallback(state->window, framebuffer_size_callback);
}

void loop(state_t *state) {
  while (!glfwWindowShouldClose(state->window)) {
    glfwSwapBuffers(state->window);
    glfwPollEvents();
  }
}
