#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "vector.hpp"
#include "shader.hpp"
#include "color.hpp"

//sample shader code
constexpr const char* vertex_code = R"shd(
#version 330 core 
layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec4 v_col;
out vec4 col;
void main() {
	col = v_col;
	gl_Position = vec4(v_pos, 0., 1.);
}
)shd";
constexpr const char* fragment_code = R"shd(
#version 330 core 
in vec4 col;
out vec4 outcol;
void main() {
    outcol = col;
}
)shd";

int main() {
    ivec2 window_size = {1080, 720};

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(window_size.x, window_size.y, "Snake", nullptr, nullptr);
    glfwMakeContextCurrent(w);

    gladLoadGL((GLADloadfunc)glfwGetProcAddress);

    shader shd = shader(vertex_code, fragment_code);

    unsigned vao, vbo;

    struct vert {
        vec2 pos;
        color col;
    } buf[] = {//example OpenGL triangle data
        {{-0.5f, -0.2f}, {255, 0, 0}},  
        {{0.0f, 0.6f}, {0, 255, 0}},  
        {{0.5f, -0.2f}, {0, 0, 255}}  
    };

    //create buffers and send buffer data
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);

    //set vertex atribbutes
    glEnableVertexAttribArray(0);//pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vert), (void*)offsetof(vert, pos));
    glEnableVertexAttribArray(1);//col
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vert), (void*)offsetof(vert, col));

    while (!glfwWindowShouldClose(w)) {
        glfwGetWindowSize(w, &window_size.x, &window_size.y);

        glViewport(0, 0, window_size.x, window_size.y);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shd.id);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
}