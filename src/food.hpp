#pragma once 
#ifndef FOOD_INCLUDE_
#define FOOD_INCLUDE_

#include "vertex.hpp"

class food {
public:
    food() {}

    void update(float dt) {
        //TODO add impl
        m_time += dt;
        cur_pos = origin + angle_vector(m_time / 100.f);
    }

    void draw(std::vector<vertex>& vec) {
        //TODO add impl
        build_shape(std::back_inserter(vec), circ(5.f, cur_pos), col_yellow);
    }

    float saturation;
    float m_time = 0.f; 
    vec2 cur_pos;
    vec2 origin;//food rotate around origin
    color col;
};

#endif//FOOD_INCLUDE_