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

//TODO add == != operators, const colors

#endif//COLOR_INCLUDE_