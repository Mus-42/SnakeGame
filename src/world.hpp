#pragma once
#ifndef WORLD_INCLUDE_
#define WORLD_INCLUDE_

#include "food.hpp"
#include "snake.hpp"

class world {
public:
    world() {}

    void update(float dt) {
        for(auto& f : m_food) f.update(dt);
        while(m_food.size() < 100) {//TODO add normal food spawn
            food f;
            f.origin = {float(rand()%2000-1000), float(rand()%2000-1000)};
            f.m_time = rand()%100/10.f;
            //f.col
            m_food.push_back(f);
        }
    }

    void draw(std::vector<vertex>& vec) {
        for(auto& f : m_food) f.draw(vec);
    }

    std::vector<food> m_food;//replase vector with other struct. quad tree or other similar data struct;
};

#endif//WORLD_INCLUDE_