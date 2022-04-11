#pragma once
#ifndef SHAPES_INCLUDE_
#define SHAPES_INCLUDE_
#include <utility>//std::swap
#include <cmath>//std::abs
#include "vector.hpp"
template<typename T>
class circle {
public:
    circle(T r = T(0), vec2_t<T> p = vec2_t<T>(0)) : radius(r), pos(p) {}
    ~circle() = default;

    T radius;
    vec2_t<T> pos;

    void update() {
        radius = std::abs(radius);
    }
};
template<typename T>
class rectangle {
public:
    rectangle() : a(0), b(0) {}
    rectangle(vec2_t<T> A, vec2_t<T> B) : a(A), b(B) { update(); }

    vec2_t<T> a, b;

    void update() {
        if (a.x < b.x) std::swap(a.x, b.x);
        if (a.y < b.y) std::swap(a.y, b.y);
    }

    bool contains(const vec2_t<T>& p) const {
        return b.x <= p.x && p.x <= a.x
            && b.y <= p.y && p.y <= a.y;
    }
    bool contains(const rectangle<T>& p) const {
        return b.x <= p.x && p.x <= a.x
            && b.y <= p.y && p.y <= a.y;
    }
};
template<typename T>
class segment {
public:
    segment() : a(0), b(0) {}
    segment(vec2_t<T> A, vec2_t<T> B) : a(A), b(B) {}
    vec2_t<T> a, b;

    //TODO add distanse to line function impl
};

using seg = segment<float>;

using circ = circle<float>;

using rect = rectangle<float>;
using irect = rectangle<int>;

#endif//SHAPES_INCLUDE_