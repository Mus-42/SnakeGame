#pragma once
#ifndef CAMERA_TRANSFORM_INCLUDE_
#define CAMERA_TRANSFORM_INCLUDE_
#include "vector.hpp"
//create 3x3 transform matrix world coords to GL screen coords (from -1 to 1)
inline float* create_2d_camera_teransform(ivec2 window_size, vec2 camera_pos = vec2(), vec2 scale = vec2(1.f)) {
    static float mat[9];
    mat[0] = scale.x / (float)window_size.x;
    mat[1] = 0.f;
    mat[2] = 0.f;

    mat[3] = 0.f;
    mat[4] = scale.x / (float)window_size.y;
    mat[5] = 0.f;

    mat[6] = -camera_pos.x * mat[0];
    mat[7] = -camera_pos.y * mat[4];
    mat[8] = 1.f;
    return mat;
}
#endif//CAMERA_TRANSFORM_INCLUDE_