#pragma once
#ifndef SNAKE_INCLUDE_
#define SNAKE_INCLUDE_

#include <vector>//std::vector
#include "vertex.hpp"
#include "vector.hpp"

class snake {
public:
    snake() : m_segments(50) {
        int p = 0;
        for(auto& v : m_segments) {
            v.pos = {30.f*(float)p++, 0.f};
            v.col = {0, 0, uint8_t(p%3 * 50 + 75)};//TODO add skin loading
        }
    }

    void draw(std::vector<vertex>& vec) {
        int i = 0;
        for(size_t sz = m_segments.size(), i = sz-1; i < sz; i--) {
            auto& s = m_segments[i];
            build_shape(std::back_inserter(vec), circ{45.f, s.pos}, col_black);//TODO add "outline" option to build_shape?
            build_shape(std::back_inserter(vec), circ{40.f, s.pos}, s.col);
        }
    }

    struct segment {
        vec2 pos;
        color col;
        //TODO add texture rect to display skins
    };

    std::vector<segment> m_segments;
};

#endif//SNAKE_INCLUDE_