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
        for(size_t sz = m_segments.size(), i = 0; i < sz; i++) {
            auto& s = m_segments[i];
            s.pos = {30.f*(float)p++, 0.f};
            s.col = {0, 0, uint8_t(p%3 * 50 + 75)};//TODO add skin loading
        }
    }

    void update(float dt) {
        static float t = 0;
        t += dt;
        for(auto& v : m_segments) v.pos.y = 50.f * sin(v.pos.x / 60.f - t);//simple sine wave animation
        update_dir();
        //TODO add position update ? 
    }

    void draw(std::vector<vertex>& vec) {
        int i = 0;
        for(size_t sz = m_segments.size(), i = sz-1; i < sz; i--) {
            auto& s = m_segments[i];
            build_shape(std::back_inserter(vec), circ{45.f, s.pos}, col_black);//TODO add "outline" option to build_shape?
            build_shape(std::back_inserter(vec), circ{40.f, s.pos}, s.col);
        }
        //display dir (debug)
        for(size_t sz = m_segments.size(), i = sz-1; i < sz; i--) {
            auto& s = m_segments[i];
            build_shape(std::back_inserter(vec), seg{s.pos, s.pos + vec2(20.f)*angle_vector(s.dir)}, col_red);
        }
    }

private:
    struct segment {
        vec2 pos;
        color col;
        //TODO add texture rect to display skins
        float dir;
    };

    std::vector<segment> m_segments;

    void update_dir() {
        for(size_t sz = m_segments.size(), i = 1; i < sz; i++)
            m_segments[i].dir = angle_of_vector(m_segments[i-1].pos-m_segments[i].pos);    
    }
};

#endif//SNAKE_INCLUDE_