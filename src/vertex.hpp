#pragma once
#ifndef VERTEX_INCLUDE_
#define VERTEX_INCLUDE_

#include <vector>//std::vector
#include <iterator>//std::back_insert_iterator
#include <cmath>//sin, cos ...

#include "vector.hpp"
#include "color.hpp"
#include "shapes.hpp"

struct vertex {
    vec2 pos;
    vec2 uv;
    color col;
};

inline void build_shape(std::back_insert_iterator<std::vector<vertex>> vec, const rect& r, color fill_color, const irect& texture_rect = irect()) {
    //TODO pass tex size as arg to calc UV?
    //TODO add uv calculation
    //first triangle
    (*vec++) = {r.a, {}, fill_color};
    (*vec++) = {{r.a.x, r.b.y}, {}, fill_color};
    (*vec++) = {{r.b.x, r.a.y}, {}, fill_color};
    //second triangle
    (*vec++) = {r.b, {}, fill_color};
    (*vec++) = {{r.a.x, r.b.y}, {}, fill_color};
    (*vec++) = {{r.b.x, r.a.y}, {}, fill_color};
}

inline void build_shape(std::back_insert_iterator<std::vector<vertex>> vec, const circ& c, color fill_color, const irect& texture_rect = irect()) {
    constexpr float pi = 3.14159265359f;
    float l = c.radius * 2.f * pi;
    size_t seg_count = std::max(size_t(l/10.f), size_t(10));
    //std::vector<vertex> ret(seg_count * 3, {{}, {}, fill_color});
    float step = 2*pi / float(seg_count);
    for(size_t i = 0; i < seg_count; i++) {//for each segment
        (*vec++) = {c.pos, {}, fill_color};
        (*vec++) = {c.pos + vec2(c.radius) * vec2(sin(i * step), cos(i * step)), {}, fill_color};
        (*vec++) = {c.pos + vec2(c.radius) * vec2(sin((i+1) * step), cos((i+1) * step)), {}, fill_color};
    }
}

inline void build_shape(std::back_insert_iterator<std::vector<vertex>> vec, const seg& s, color color, float thickness = 2.f) {   
    //TODO add configurable thickness as arg?
    auto s_dir = s.b - s.a;
    auto d = normalize(vec2(s_dir.y, -s_dir.x)) * vec2(thickness / 2.f);//normal vector to seg s lengt of thickness / 2.f

    (*vec++) = {s.a + d, {}, color};
    (*vec++) = {s.b + d, {}, color};
    (*vec++) = {s.a - d, {}, color};

    (*vec++) = {s.a - d, {}, color};
    (*vec++) = {s.b - d, {}, color};
    (*vec++) = {s.b + d, {}, color};
}


#endif//VERTEX_INCLUDE_