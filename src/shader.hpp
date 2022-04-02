#pragma once
#ifndef SHADER_INCLUDE_
#define SHADER_INCLUDE_

#ifndef __gl_h_
#error "must be included after gl.h"
#endif

#include <string>
#include <unordered_map>//uniforms cash
#include <fstream>
#include <iostream>     //logging

#include "id.hpp"

class shader {
public:
    shader() {}
    shader(const std::string& vertex_code, const std::string& fragment_code) {
        unsigned vertex_shader, fragment_shader, program = 0;
        int success;
        const char* str;

        //create vertex & fragment shaders
        str = vertex_code.c_str();
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, (const char**)(&str), NULL);
        glCompileShader(vertex_shader);
        str = fragment_code.c_str();
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, (const char**)(&str), NULL);
        glCompileShader(fragment_shader);
        program = glCreateProgram();

        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
            static char info_log[1024];
            glGetProgramInfoLog(program, 1024, NULL, info_log);
            std::cout << info_log << std::endl;//TODO add normal log
        }
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        id = program;
    }
    static shader load_from_file(const std::string& vertex_file, const std::string& fragment_file) {
        std::string vertex_code, fragment_code;
        std::ifstream in;

        in.open(vertex_file);
        if(in.is_open()) std::getline(in, vertex_code, '\0');
        in.close();

        in.open(fragment_file);
        if(in.is_open()) std::getline(in, fragment_code, '\0');
        in.close();
        
        if(vertex_code.empty() || fragment_code.empty()) return shader();//TODO add log / throw exception?
        else return shader(vertex_code, fragment_code);
    }

    unsigned get_uniform_loc(const std::string& uniform) const {
        auto f = uniform_loc_cash.find(uniform);
        if(f != uniform_loc_cash.end()) return f->second;
        else return uniform_loc_cash[uniform] = (unsigned)glGetUniformLocation(id, uniform.c_str());
    }

    static void unload_shader_by_id(unsigned id) {
        glDeleteProgram(id);
    }

    id_t<unload_shader_by_id> id;
protected:
    mutable std::unordered_map<std::string, unsigned> uniform_loc_cash; 
};
#endif//SHADER_INCLUDE_