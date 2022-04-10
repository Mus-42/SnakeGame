#pragma once
#ifndef IMAGE_INCLUDE_
#define IMAGE_INCLUDE_

#include "color.hpp"
#include "vector.hpp"

class image {
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

    static image load_from_memory(uvec2 size, color* data) {
        image img;
        img.m_pixels = data;
        img.m_size = size;
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