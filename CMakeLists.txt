cmake_minimum_required(VERSION 3.11)
project(learnOpenGL VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)

set(GLFW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
set(GLAD_SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/glad)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

# This is so neovim LSP can get code completion :)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(glad STATIC lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3-stable
  SOURCE_DIR     ${GLFW_SOURCE_DIR}  # <-- force it here so editor sees it
)

FetchContent_MakeAvailable(glfw)
find_package(OpenGL REQUIRED)

include_directories(
    lib/glfw/include
    lib/glad/include
)

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(learnOpenGL ${SRC_FILES})

target_link_libraries(learnOpenGL glfw glad OpenGL::GL ${CMAKE_DL_LIBS})
