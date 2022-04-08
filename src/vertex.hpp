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

inline std::vector<vertex> build_shape(const rect& r, color fill_color, const irect& texture_rect = irect()) {//TODO pass tex size as arg to calc UV?
    std::vector<vertex> ret(6, {{}, {}, fill_color});
    //first triangle
    ret[0].pos = r.a;
    ret[1].pos = {r.a.x, r.b.y};
    ret[2].pos = {r.b.x, r.a.y};
    //second triangle
    ret[3].pos = r.b;
    ret[4].pos = {r.a.x, r.b.y};
    ret[5].pos = {r.b.x, r.a.y};
    //TODO add uv calculation
    return ret;
}

inline std::vector<vertex> build_shape(const circ& c, color fill_color, const irect& texture_rect = irect()) {
    std::vector<vertex> ret(0);//TODO calc size
    //TODO add impl
    return ret;
}

#endif//VERTEX_INCLUDE_