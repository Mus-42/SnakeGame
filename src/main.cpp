#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shader.hpp"
#include "process_gl_errors.hpp"
#include "2d_camera_transform.hpp"
#include "display_shader.hpp"
#include "snake.hpp"
#include "texture.hpp"

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
    
    constexpr size_t max_vert_size = size_t(3e5);
    //vert.reserve(max_vert_size);

    snake s;
    

    unsigned vao, vbo;

    //create buffers and send buffer data
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(vertex), vert.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, max_vert_size * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);

    //set vertex atribbutes
    glEnableVertexAttribArray(0);//pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
    glEnableVertexAttribArray(2);//col
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, col));
    glBindVertexArray(0);

    glDisable(GL_CULL_FACE);

    color default_texture_fill_color = {255, 255, 255, 0};
    texture default_texture = texture::load_from_memory({1, 1}, &default_texture_fill_color, false);//1x1 white texture


    glUseProgram(display_shd.id);
    glUniform1i(display_shd.get_uniform_loc("tex"), 1);//GL_TEXTURE0 -> 0
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, default_texture.id.id);

    process_gl_errors("tex creations");

    double prev_frame_time = glfwGetTime();
    while (!glfwWindowShouldClose(w)) {
        glfwGetWindowSize(w, &window_size.x, &window_size.y);
        double t = glfwGetTime();
        float dt = float(t - prev_frame_time);
        prev_frame_time = t;

        s.update(dt);

        vert.clear();

        s.draw(vert);
        build_shape(std::back_inserter(vert), seg{{0., 0.}, {10., 0.}}, col_cyan);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, std::min(max_vert_size, vert.size()) * sizeof(vertex), vert.data());

        glUseProgram(display_shd.id);
        glUniformMatrix3fv(display_shd.get_uniform_loc("camera_transform"), 1, GL_FALSE, create_2d_camera_teransform(window_size));

        glViewport(0, 0, window_size.x, window_size.y);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (unsigned)vert.size());
        glBindVertexArray(0);

        process_gl_errors("in game loop");

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
}