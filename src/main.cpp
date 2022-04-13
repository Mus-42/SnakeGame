#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shader.hpp"
#include "process_gl_errors.hpp"
#include "2d_camera_transform.hpp"
#include "shaders_src.hpp"
#include "snake.hpp"
#include "world.hpp"
#include "texture.hpp"

//TODO move all global variables in single class?
vec2 world_mouse_pos = {0, 0};
vec2 skreen_mouse_pos = {0, 0};
vec2 camera_pos = {0, 0};
ivec2 window_size = {1080, 720};

unsigned vert_vao = 0, vert_vbo = 0;
unsigned background_vao = 0, background_vbo = 0;

constexpr size_t max_vert_size = size_t(3e5);
std::vector<vertex> vert;

void init_gl_objects();

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(window_size.x, window_size.y, "Snake", nullptr, nullptr);
    glfwMakeContextCurrent(w);

    gladLoadGL((GLADloadfunc)glfwGetProcAddress);

    glfwSetCursorPosCallback(w, [](GLFWwindow* window, double xpos, double ypos) {
        skreen_mouse_pos = vec2((float)xpos - window_size.x/2.f, window_size.y/2.f - (float)ypos);//scale here?
    });

    glDisable(GL_CULL_FACE);

    init_gl_objects();
    
    shader display_shd = shader(display_shd_vertex_code, display_shd_fragment_code);//vertex display shader
    shader background_shd = shader(background_shd_vertex_code, background_shd_fragment_code);//background
    
    snake test_snake;
    world test_world;

    texture background_texture = texture::load_from_image(image::load_from_file("bacground.png"));//TODO add normal resorce folder

    color default_texture_fill_color = {255, 255, 255, 0};
    texture default_texture = texture::load_from_memory({1, 1}, &default_texture_fill_color, false);//1x1 white texture

    glUseProgram(display_shd.id);
    glUniform1i(display_shd.get_uniform_loc("tex"), 0);//GL_TEXTURE0 -> 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, default_texture.id.id);
    
    glUseProgram(background_shd.id);
    glUniform1i(background_shd.get_uniform_loc("bacground_tex"), 1);//GL_TEXTURE1 -> 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, background_texture.id.id);

    double prev_frame_time = glfwGetTime();
    while (!glfwWindowShouldClose(w)) {
        glfwGetWindowSize(w, &window_size.x, &window_size.y);
        double t = glfwGetTime();
        float dt = std::min(float(t - prev_frame_time), 0.2f);
        prev_frame_time = t;
        world_mouse_pos = skreen_mouse_pos + camera_pos;
        vert.clear();

        auto p = test_snake.get_head_pos();
        build_shape(std::back_inserter(vert), seg{world_mouse_pos, world_mouse_pos + vec2(14.f)*normalize(world_mouse_pos - p)}, col_magenta);

        test_snake.set_direction(world_mouse_pos);
        

        test_snake.update(dt);
        test_world.update(dt);
        
        camera_pos = test_snake.get_head_pos();//TODO add lerp


        test_snake.draw(vert);
        test_world.draw(vert);
        //build_shape(std::back_inserter(vert), seg{{0., 0.}, {10., 0.}}, col_cyan);

        glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, std::min(max_vert_size, vert.size()) * sizeof(vertex), vert.data());

        float* cam_transform = create_2d_camera_teransform(window_size, camera_pos);

        glUseProgram(display_shd.id);
        glUniformMatrix3fv(display_shd.get_uniform_loc("camera_transform"), 1, GL_FALSE, cam_transform);
        glUseProgram(background_shd.id);
        glUniformMatrix3fv(background_shd.get_uniform_loc("camera_transform"), 1, GL_FALSE, cam_transform);

        glViewport(0, 0, window_size.x, window_size.y);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw background
        glUseProgram(background_shd.id);
        glBindVertexArray(background_vbo);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        //display vertices
        glUseProgram(display_shd.id);
        glBindVertexArray(vert_vao);
        glDrawArrays(GL_TRIANGLES, 0, (unsigned)vert.size());

        glBindVertexArray(0);

        process_gl_errors("in game loop");

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
}

void init_gl_objects() {
    //vertex display

    //create buffers
    glGenVertexArrays(1, &vert_vao);
    glGenBuffers(1, &vert_vbo);
    glBindVertexArray(vert_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
    //glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(vertex), vert.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, max_vert_size * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);

    //set vertex atribbutes
    glEnableVertexAttribArray(0);//pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
    glEnableVertexAttribArray(2);//col
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, col));


    //background
    glGenVertexArrays(1, &background_vao);
    glGenBuffers(1, &background_vbo);
    glBindVertexArray(background_vao);
    glBindBuffer(GL_ARRAY_BUFFER, background_vbo);

    //2 trangles -> background. this index using in vertex shader to calculate uv & pos
    vec2 background_vbo_data[] = {
        {-1.f, 1.f},
		{1.f, -1.f},
		{-1.f, -1.f},
		{-1.f, 1.f},
		{1.f, -1.f},
		{1.f, 1.f},
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(background_vbo_data), background_vbo_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);//pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), nullptr);

    glBindVertexArray(0);
}