#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shader.hpp"
#include "process_gl_errors.hpp"
#include "2d_camera_transform.hpp"
#include "display_shader.hpp"
#include "vertex.hpp"

int main() {
    ivec2 window_size = {1080, 720};

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(window_size.x, window_size.y, "Snake", nullptr, nullptr);
    glfwMakeContextCurrent(w);

    gladLoadGL((GLADloadfunc)glfwGetProcAddress);

    shader display_shd = shader(display_shd_vertex_code, display_shd_fragment_code);

    std::vector<vertex> vert;
    {
        auto circle_vert = build_shape(circ(50.f, {150.f, 50.f}), col_blue);
        auto rect_vert = build_shape(rect({-20.f, -20.f}, {20.0f, 20.f}), col_green);
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
        glUniformMatrix3fv(display_shd.get_uniform_loc("camera_transform"), 1, GL_FALSE, create_2d_camera_teransform(window_size));

        glViewport(0, 0, window_size.x, window_size.y);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(display_shd.id);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (unsigned)vert.size());
        glBindVertexArray(0);

        process_gl_errors();

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
}