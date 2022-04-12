#pragma once
#ifndef SNAKE_INCLUDE_
#define SNAKE_INCLUDE_

#include <cassert>
#include "vertex.hpp"

class snake {
public:
    static constexpr float dist = 25.f;//distanse between segments

    snake() : m_segments(120) {
        int p = 0;
        m_segments[0].dir = 0.f;
        for(size_t sz = m_segments.size(), i = 0; i < sz; i++) {
            auto& s = m_segments[i];
            s.pos = {dist*(float)p++, 0.f};
            s.pos.y = 1.5f * dist * sin(s.pos.x / 60.f);
            s.col = {0, 0, uint8_t(p%3 * 50 + 75)};//TODO add skin loading
        }
        update_dir();
    }

    void update(float dt) {
        //TODO add position update ? 
        float speed = 150.f;
        auto& h = m_segments.front();//head
        constexpr float pi = 3.141592653589793f;
        
        //h.dir = std::fmod(std::fmod(h.dir, 2.f*pi) + 2.f*pi, 2.f*pi);
        //h.dir = std::fmod(h.dir, 2.f*pi);
        auto clamp_ang = [pi](float a)->float{        
            if(a > +pi) a -= 2.f*pi;
            if(a < -pi) a += 2.f*pi;
            return a;
        };
        h.dir = clamp_ang(h.dir);
        float ddir1 = target_dir - h.dir;
        float ddir2 = -ddir1;
        ddir1 = clamp_ang(ddir1);
        ddir2 = clamp_ang(ddir2);
        float ddir = std::abs(ddir1) < std::abs(ddir2) ? ddir1 : ddir2;
        float dir_speed = 1.5f;
        h.dir -= dir_speed * dt * std::copysign(1.f, ddir);
        //if(std::isfinite(h.dir)) 
        h.pos += vec2(dt * speed) * angle_vector(h.dir);
        for(size_t sz = m_segments.size(), i = 1; i < sz; i++) {
            auto& s = m_segments[i];
            auto& l = m_segments[i-1];

            vec2 target = l.pos - vec2(dist) * angle_vector(s.dir);

            float cur_l = length(l.pos - s.pos);
            float dl = std::max(cur_l - dist, 0.f);

            s.pos += vec2(std::clamp(dt * speed, 0.f, dl)) * angle_vector(s.dir);
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
            build_shape(std::back_inserter(vec), seg{s.pos, s.pos + vec2(14.f)*angle_vector(s.dir)}, col_red);
        }
        build_shape(std::back_inserter(vec), seg{m_segments.front().pos, m_segments.front().pos + vec2(14.f)*angle_vector(target_dir)}, col_red);
    }

    void set_direction(vec2 to) {
        auto d = to-m_segments.front().pos;
        if(length_sqr(d) > dist * dist) {
            target_dir = angle_of_vector(d);
        }
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

    float target_dir = 0.f;
    std::vector<segment> m_segments;

    void update_dir() {
        for(size_t sz = m_segments.size(), i = 1; i < sz; i++)
            m_segments[i].dir = angle_of_vector(m_segments[i-1].pos-m_segments[i].pos);    
    }
};

#endif//SNAKE_INCLUDE_