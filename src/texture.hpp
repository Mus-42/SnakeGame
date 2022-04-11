#pragma once
#ifndef TEXTURE_INCLUDE_
#define TEXTURE_INCLUDE_

#ifndef __gl_h_
#error "must be included after gl.h"
#endif

#include "image.hpp"
#include "id.hpp"

class texture {
public:
    texture() {}
    static texture load_from_memory(uvec2 size, const color* ptr, bool lerp = true) {
        texture tex;
        tex.m_size = size;
        glGenTextures(1, &tex.id.id);
        glBindTexture(GL_TEXTURE_2D, tex.id);     
        if(lerp) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)ptr); 
        glBindTexture(GL_TEXTURE_2D, 0);
        return tex;
    }
    static texture load_from_image(const image& img, bool lerp = true) {
        return load_from_memory(img.size(), img.data(), lerp);
    }

    //TODO add update function

    uvec2 size() const {
        return m_size;
    }

    static void unload_texture_by_id(unsigned id) {
        glDeleteTextures(1, &id);
    }
    id_t<unload_texture_by_id> id;
protected:
    uvec2 m_size;
};

#endif//TEXTURE_INCLUDE_