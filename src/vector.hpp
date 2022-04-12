#pragma once
#ifndef VECTOR_INCLUDE_
#define VECTOR_INCLUDE_

#include <cmath> //sin, cos ...

template<typename T>
struct vec2_t {
    constexpr vec2_t(T v = T(0)) : x(v), y(v) {}
    constexpr vec2_t(T X, T Y) : x(X), y(Y) {}
    constexpr vec2_t(const vec2_t&) = default;
    constexpr vec2_t& operator=(const vec2_t&) = default;
    ~vec2_t() = default;

    template<typename T2>
    constexpr vec2_t(const vec2_t<T2>& v2) : x(static_cast<T2>(v2.x)), y(static_cast<T2>(v2.y)) {}

    T x, y;
};
template<typename T>
constexpr bool operator==(const vec2_t<T>& a, const vec2_t<T>& b) {
    return a.x == b.x && a.y == b.y;
}
template<typename T>
constexpr bool operator!=(const vec2_t<T>& a, const vec2_t<T>& b) {
    return a.x != b.x || a.y != b.y;
}
template<typename T>
constexpr vec2_t<T> operator+(const vec2_t<T>& a, const vec2_t<T>& b) {
    return {a.x + b.x, a.y + b.y};
}
template<typename T>
constexpr vec2_t<T> operator-(const vec2_t<T>& a, const vec2_t<T>& b) {
    return {a.x - b.x, a.y - b.y};
}
template<typename T>
constexpr vec2_t<T> operator*(const vec2_t<T>& a, const vec2_t<T>& b) {
    return {a.x * b.x, a.y * b.y};
}
template<typename T>
constexpr vec2_t<T> operator/(const vec2_t<T>& a, const vec2_t<T>& b) {
    return {a.x / b.x, a.y / b.y};
}
template<typename T>
constexpr vec2_t<T>& operator+=(vec2_t<T>& a, const vec2_t<T>& b) {
    a = a+b;
    return a;
}
template<typename T>
constexpr vec2_t<T>& operator-=(vec2_t<T>& a, const vec2_t<T>& b) {
    a = a-b;
    return a;
}
template<typename T>
constexpr vec2_t<T>& operator*=(vec2_t<T>& a, const vec2_t<T>& b) {
    a = a*b;
    return a;
}
template<typename T>
constexpr vec2_t<T>& operator/=(vec2_t<T>& a, const vec2_t<T>& b) {
    a = a/b;
    return a;
}

using vec2 = vec2_t<float>;
using ivec2 = vec2_t<int>;
using uvec2 = vec2_t<unsigned>;

template<typename T>
T length_sqr(const vec2_t<T>& v) {
    return v.x * v.x + v.y * v.y;
}

template<typename T>
T length(const vec2_t<T>& v) {
    return std::sqrt(length_sqr(v));
}

template<typename T>
vec2_t<T> normalize(const vec2_t<T>& v) {
    return v / vec2_t<T>(length(v));
}

template<typename T>
vec2_t<T> angle_vector(T angle) {
    return vec2_t<T>(std::sin(angle), std::cos(angle));
}

template<typename T>
T angle_of_vector(const vec2_t<T>& v) {
    auto n = normalize(v);//normalized vector
    return (T)std::atan2(n.x, n.y);
}

//TODO add min, max, clamp, round ... functions for vector? (same as GLSL)

#endif//VECTOR_INCLUDE_