#pragma once
#ifndef COLOR_INCLUDE_
#define COLOR_INCLUDE_

#include <cstdint>//uint8_t

struct color {
public:
    constexpr color() : r(0), g(0), b(0), a(255) {}
    constexpr color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255) : r(R), g(G), b(B), a(A) {}

    ~color() = default;
    color(const color&) = default;

    uint8_t r, g, b, a;
};

bool operator==(const color& a, const color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

bool operator!=(const color& a, const color& b) {
    return !(a == b);
}


constexpr color col_white = { 255, 255, 255 };
constexpr color col_black = { 0, 0, 0 };

constexpr color col_transparent = { 0, 0, 0, 0 };

constexpr color col_red = { 255, 0, 0 };
constexpr color col_green = { 0, 255, 0 };
constexpr color col_blue = { 0, 0, 255 };

constexpr color col_yellow = { 255, 255, 0 };
constexpr color col_magenta = { 255, 0, 255 };
constexpr color col_cyan = { 0, 255, 255 };

#endif//COLOR_INCLUDE_