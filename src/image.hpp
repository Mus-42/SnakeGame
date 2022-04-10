#pragma once
#ifndef IMAGE_INCLUDE_
#define IMAGE_INCLUDE_

#include <string>

#include <stb_image.h>

#include "color.hpp"
#include "vector.hpp"

class image {
public:
    image() : m_pixels(nullptr), m_size(0) {}
    ~image() {
        if(m_pixels) delete[] m_pixels;
    }
    image(const image& img) : m_pixels(new color[img.m_size.x * img.m_size.y]), m_size(img.m_size) {
        if(img.m_pixels) for(size_t i = 0, s = img.m_size.x * img.m_size.y; i < s; i++) m_pixels[i] = img.m_pixels[i];
    }
    image(image&& img) : m_pixels(img.m_pixels), m_size(img.m_size) {
        img.m_pixels = nullptr;
    }

    static image load_from_memory(uvec2 size, const color* data) {
        image img;
        //copy
        img.m_size = size;
        if(data) {
            img.m_pixels = new color[size.x * size.y];
            for(size_t i = 0, s = img.m_size.x * img.m_size.y; i < s; i++) img.m_pixels[i] = data[i];
        }
        return img;
    }
    static image load_from_file(const std::string& filename) {
        int sz_x, sz_y, n;
        unsigned char *data = stbi_load(filename.c_str(), &sz_x, &sz_y, &n, 4);
        image img = load_from_memory({(unsigned)sz_x, (unsigned)sz_y}, reinterpret_cast<color*>(data));
        stbi_image_free(data);
        return img;
    }
    

    uvec2 size() const {
        return m_size;
    }
    color* data() {
        return m_pixels;
    }
    const color* data() const {
        return m_pixels;
    }  
private:
    color* m_pixels;
    uvec2 m_size;
};

#endif//IMAGE_INCLUDE_