#pragma once 
#ifndef FOOD_INCLUDE_
#define FOOD_INCLUDE_

#include "vertex.hpp"

class food {
public:
    food() {}

    void update(float dt) {
        //TODO add impl
        //cur_pos = origin + ...;
    }

    void draw(std::vector<vertex>& vec) {
        //TODO add impl
    }

    float saturation;
    vec2 cur_pos;
    vec2 origin;//food rotate around origin
};

#endif//FOOD_INCLUDE_