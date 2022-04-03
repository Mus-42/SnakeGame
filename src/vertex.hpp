#pragma once
#ifndef VERTEX_INCLUDE_
#define VERTEX_INCLUDE_

#include <vector>//std::vector

#include "vector.hpp"
#include "color.hpp"
#include "shapes.hpp"

struct vertex {
    vec2 pos;
    vec2 uv;
    color col;
};

inline std::vector<vertex> build_shape(const rect& r, const irect& texture_rect = irect()) {
    std::vector<vertex> ret(4);
    //TODO add impl
    return ret;
}

inline std::vector<vertex> build_shape(const circ& c, const irect& texture_rect = irect()) {
    std::vector<vertex> ret(0);//TODO calc size
    //TODO add impl
    return ret;
}

#endif//VERTEX_INCLUDE_