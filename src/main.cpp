#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "vector.hpp"
#include "shader.hpp"

int main() {
    ivec2 window_size = {1080, 720};

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(window_size.x, window_size.y, "Snake", nullptr, nullptr);
    glfwMakeContextCurrent(w);

    gladLoadGL((GLADloadfunc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(w)) {
        glfwGetWindowSize(w, &window_size.x, &window_size.y);

        glViewport(0, 0, window_size.x, window_size.y);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
}