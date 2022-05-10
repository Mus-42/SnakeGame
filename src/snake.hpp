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
    virtual ~snake() = default;

    virtual void update(float dt) {
        update_pos(dt);
    }

    void update_pos(float dt) {
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
        float dir_speed = 2.5f;
        h.dir -= dir_speed * dt * std::copysign(1.f, ddir);
        h.pos += vec2(dt * speed) * angle_vector(h.dir);

        auto cof = [](float t1) {
            //t1 = std::clamp(t1, 0.f, 1.f);
            float t2 = t1 * t1;
            float t3 = t2 * t1;          
            return std::make_tuple(-t3 + 3*t2 - 3*t1 + 1, 3*t3 - 6*t2 + 4, -3*t3 + 3*t2 + 3*t1 + 1, t3);
        };
        auto cb = [cof](auto v0, auto v1, auto v2, auto v3, float t) {
            auto [t0, t1, t2, t3] = cof(t);
            using res_t = decltype(v0);//result type
            return v0 * res_t(t0) + v1 * res_t(t1) + v2 * res_t(t2) + v3 * res_t(t3);
        };

        for(size_t sz = m_segments.size(), i = 1; i < sz; i++) {
            auto& s = m_segments[i];
            auto& l = m_segments[i-1];//closest to head

            /* simple way but inaccurate
                vec2 target = l.pos - vec2(dist) * angle_vector(s.dir);
                float cur_l = length(l.pos - s.pos);
                float dl = std::max(cur_l - dist, 0.f);
                s.pos += vec2(std::clamp(dt * speed, 0.f, dl)) * angle_vector(s.dir);
            */
           
            auto v0 = i + 1 < sz ? m_segments[i+1].pos : s.pos;
            auto v1 = s.pos;
            auto v2 = l.pos;
            auto v3 = i > 1 ? m_segments[i-2].pos : l.pos;

            float t = 0.f;
            
            //TODO more accurate calculation?
            //auto df = [&](float t) -> vec2 {
            //    return v0 * vec2(3 * (1 - t) * (-1 + t)) + v1 * vec2(3 * (3 * t - 4) * t) + v3 * vec2(3 * t * t) + v2 * vec2(3 * (1 + 2 * t - 3 * t * t));
            //};
            //constexpr float dt = 1e-2f;
            //float sum = length(df(0.f)) * dt, t2 = 1.f, sum2 = 0.f;
            //float dp = dt * speed;
            //while (sum < dp) {
            //    t += dt;
            //    sum += length(df(t)) * dt;
            //}
            t = (1.f - dt)/10.f;
            
            t = std::clamp(t, 0.f, 1.f);
            s.pos = vec2(1.f - t) * v1 + vec2(t) * v2;
            //s.pos = cb(v0, v1, v2, v3, t);
        }

        /*
            some math stuff
            TODO remove it
            v0 * (-x^3 + 3*x^2 - 3*x + 1) +
            v1 * (3*x^3 - 6*x^2 + 4) +
            v2 * (-3*x^3 + 3*x^2 + 3*x + 1) +
            v3 * (x^3)

            
            v0 * (-x^3 + 3*x^2 - 3*x + 1) + v1 * (3*x^3 - 6*x^2 + 4) + v2 * (-3*x^3 + 3*x^2 + 3*x + 1) + v3 * (x^3)

            f(x) = 3*(-(v0 * (-1 + x)^2) + x*(-4 * v1 + 3 * v1 x + v3 * x) + v2 * (1 + 2 * x - 3 * x^2))
            f(x) = 3*(-(a * (-1 + x)^2) + x*(-4 * b + 3 * b x + d * x) + c * (1 + 2 * x - 3 * x^2))
            3(-(v_{0} (-1 + x)^2) + x (-4 v_{1} + 3 v1 x + v_{3} x) + v_{2} (1 + 2 x - 3 x^2))
            sqrt(1 + (3(-(v_{0} (-1 + x)^2) + x (-4 v_{1} + 3 v_{1} x + v_{3} x) + v_{2} (1 + 2 x - 3 x^2)))^2)

            v_{0} * (-x^3 + 3*x^2 - 3*x + 1) + v_{1} * (3*x^3 - 6*x^2 + 4) + v_{2} * (-3*x^3 + 3*x^2 + 3*x + 1) + v_{3} * (x^3)
        */

        update_dir();
    }

    virtual void draw(std::vector<vertex>& vec) {
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