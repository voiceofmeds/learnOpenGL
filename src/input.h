#ifndef _INPUT_H
#define _INPUT_H

#include <GLFW/glfw3.h>

// maybe this could cause an error later?
extern void (*key_handlers[]) (GLFWwindow *window);
extern unsigned int key_handler_size;

void terminate_glfw(GLFWwindow *window);
#endif
