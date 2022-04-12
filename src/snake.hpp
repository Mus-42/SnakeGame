#pragma once
#ifndef SNAKE_INCLUDE_
#define SNAKE_INCLUDE_

#include "vertex.hpp"

class snake {
public:
    snake() : m_segments(50) {
        int p = 0;
        for(size_t sz = m_segments.size(), i = 0; i < sz; i++) {
            auto& s = m_segments[i];
            s.pos = {15.f*(float)p++, 0.f};
            s.pos.y = 25.f * sin(s.pos.x / 60.f);
            s.col = {0, 0, uint8_t(p%3 * 50 + 75)};//TODO add skin loading
        }
        update_dir();
    }

    void update(float dt) {
        //TODO add position update ? 
        float speed = 150.f;
        auto& h = m_segments.front();//head
        if(std::isfinite(h.dir)) 
            h.pos += vec2(dt * speed) * angle_vector(h.dir);
        for(size_t sz = m_segments.size(), i = 1; i < sz; i++) {
            auto& s = m_segments[i];
            auto& l = m_segments[i-1];

            constexpr float dist = 15.f;

            vec2 target = l.pos - vec2(dist) * angle_vector(s.dir);

            float cur_l = length(l.pos - s.pos);
            if(cur_l <= dist) continue;//TODO fix it

            vec2 new_pos = s.pos + vec2(dt * speed) * angle_vector(s.dir);

            s.pos = new_pos;
        }

        update_dir();
    }

    void draw(std::vector<vertex>& vec) {
        int i = 0;
        for(size_t sz = m_segments.size(), i = sz-1; i < sz; i--) {
            auto& s = m_segments[i];
            build_shape(std::back_inserter(vec), circ{22.f, s.pos}, col_black);//TODO add "outline" option to build_shape? or add texture with outline?
            build_shape(std::back_inserter(vec), circ{20.f, s.pos}, s.col);
        }
        //display dir (debug)
        for(size_t sz = m_segments.size(), i = sz-1; i < sz; i--) {
            auto& s = m_segments[i];
            build_shape(std::back_inserter(vec), seg{s.pos, s.pos + vec2(20.f)*angle_vector(s.dir)}, col_red);
        }
    }

    void set_direction(vec2 to) {
        m_segments.front().dir = angle_of_vector(to-m_segments.front().pos);//TODO add 
    }
    vec2 get_head_pos() const {
        return m_segments.front().pos;
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