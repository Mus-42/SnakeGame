#pragma once
#ifndef VERTEX_INCLUDE_
#define VERTEX_INCLUDE_

#include <vector>//std::vector
#include <cmath>//sin, cos ...

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
    constexpr float pi = 3.14159265359f;
    float l = c.radius * 2.f * pi;
    size_t seg_count = std::max(size_t(l/5.f), size_t(10));
    std::vector<vertex> ret(seg_count * 3, {{}, {}, fill_color});
    float step = 2*pi / float(seg_count);
    for(size_t i = 0; i < seg_count; i++) {//for each segment
        ret[i * 3 + 0].pos = c.pos;
        ret[i * 3 + 1].pos = c.pos + vec2(c.radius) * vec2(sin(i * step), cos(i * step));
        ret[i * 3 + 2].pos = c.pos + vec2(c.radius) * vec2(sin((i+1) * step), cos((i+1) * step));
    }
    return ret;
}

#endif//VERTEX_INCLUDE_