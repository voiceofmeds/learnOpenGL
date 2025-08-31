#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// we use snake_case for our own functions
// camelCase are glfw/glad functions
// this is to easily distinguish between them

typedef struct {
  GLFWwindow *window;
  unsigned int width;
  unsigned int height;
  char *title;
  GLFWmonitor *monitor;
  GLFWwindow *share;
} state_t;

void glfw_error_callback(const int error, const char* description);
void init_glfw(void);
void init_window(state_t *state);

int main(void) {
  // we izero-initialize the state
  state_t state = {
    .width = 800,
    .height = 600,
    .title = "Cube"
  };

  glfwSetErrorCallback(glfw_error_callback);
  init_glfw();

  init_window(&state);

  return 0;
}

void glfw_error_callback(const int error, const char* description) {
  fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

void init_glfw(void) {
  // if initializing glfw fails exit the program as it is critical
  if (!glfwInit()) {
    glfwTerminate();
    exit(-2);
  };

  // we set up the opengl version to 3.3 and use the core profile
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
  // if creating the window fails exit the program as it is also critical
  if (window == NULL) {
    glfwTerminate();
    exit(-2);
  };
  // we make state->window point to this new window
  // then we make the current context the newly made window
  state->window = window;
  glfwMakeContextCurrent(state->window);
}
