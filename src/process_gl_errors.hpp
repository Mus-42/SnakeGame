#pragma once
#ifndef PROCESS_GL_ERRORS_INCLUDE_
#define PROCESS_GL_ERRORS_INCLUDE_

#ifndef __gl_h_
#error "must be included after gl.h"
#endif

#include <iostream>
#include <algorithm>//std::clamp
#include <string>

inline void process_gl_errors(const std::string& message = std::string()) {
    static constexpr const char* codes[] = {
        "UNKNOWN ERROR",
        "GL_INVALID_ENUM",
        "GL_INVALID_VALUE",
        "GL_INVALID_OPERATION",
        "GL_OUT_OF_MEMORY",
        "GL_INVALID_FRAMEBUFFER_OPERATION",
        "GL_CONTEXT_LOST",
        "UNKNOWN ERROR"
    };
    constexpr size_t offset = GL_INVALID_ENUM;
    unsigned err = 0;
    while(err = glGetError() != GL_NO_ERROR) 
        std::cout << "[OpenGL] Error: " << codes[std::clamp(int(err - offset) + 1, 0, 7)] << ' ' <<  message << std::endl;
}
#endif//PROCESS_GL_ERRORS_INCLUDE_