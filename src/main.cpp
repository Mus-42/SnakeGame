#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shader.hpp"
#include "process_gl_errors.hpp"
#include "vertex.hpp"

//sample shader code
constexpr const char* vertex_code = R"shd(
#version 330 core 
layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec4 v_col;
out vec4 col;
void main() {
	col = v_col;
    vec2 pos = v_pos;
	gl_Position = vec4(pos, 0.5, 1.);
}
)shd";
constexpr const char* fragment_code = R"shd(
#version 330 core 
in vec4 col;
out vec4 outcol;
void main() {
    outcol = vec4(col);
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

    std::vector<vertex> vert;
    {
        auto circle_vert = build_shape(circ(0.3f, {0.5f, 0.2f}), col_blue);
        auto rect_vert = build_shape(rect({-0.2f, -0.2f}, {0.2f, 0.2f}), col_green);
        vert.reserve(circle_vert.size() + rect_vert.size());
        vert.insert(vert.end(), circle_vert.begin(), circle_vert.end());
        vert.insert(vert.end(), rect_vert.begin(), rect_vert.end());
    }
    

    unsigned vao, vbo;

    //create buffers and send buffer data
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(vertex), vert.data(), GL_STATIC_DRAW);

    //set vertex atribbutes
    glEnableVertexAttribArray(0);//pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
    glEnableVertexAttribArray(1);//col
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, col));
    glBindVertexArray(0);

    glDisable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(w)) {
        glfwGetWindowSize(w, &window_size.x, &window_size.y);

        glViewport(0, 0, window_size.x, window_size.y);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shd.id);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (unsigned)vert.size());
        glBindVertexArray(0);

        process_gl_errors();

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
}