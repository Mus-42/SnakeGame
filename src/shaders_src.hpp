#pragma once
#ifndef DISPLAY_SHADER_INCLUDE_
#define DISPLAY_SHADER_INCLUDE_

//display vertices shd
constexpr const char* display_shd_vertex_code = R"shd(
    #version 330 core 
    layout(location = 0) in vec2 v_pos;
    layout(location = 1) in vec2 v_uv;
    layout(location = 2) in vec4 v_col;
    
    uniform mat3 camera_transform;
    
    out vec4 col;
    out vec2 uv;

    void main() {
    	col = v_col;
        uv = v_uv;
        vec3 pos = camera_transform * vec3(v_pos, 1.);
    	gl_Position = vec4(pos.xy, 0.5, 1.);
    }
)shd";
constexpr const char* display_shd_fragment_code = R"shd(
    #version 330 core 
    uniform sampler2D tex;

    in vec4 col;
    in vec2 uv;

    out vec4 outcol;

    void main() {
        outcol = texture(tex, uv) * col;
    }
)shd";

//background shd
constexpr const char* background_shd_vertex_code = R"shd(
    #version 330 core 
    layout(location = 0) in vec2 v_pos;
    uniform mat3 camera_transform;
    
    out vec2 pix_pos;

    void main() {
        pix_pos = (inverse(camera_transform)*vec3(v_pos.xy, 1.)).xy;
    	gl_Position = vec4(v_pos.xy, 0.5, 1.);
    }
)shd";
constexpr const char* background_shd_fragment_code = R"shd(
    #version 330 core 
    uniform sampler2D bacground_tex;
  
    in vec2 pix_pos;

    out vec4 outcol;

    void main() {
        vec2 size = vec2(textureSize(bacground_tex, 0));
        outcol = texture(bacground_tex, fract((floor(pix_pos) + 0.5) / size));
    }
)shd";

//light display shd
constexpr const char* light_display_shd_vertex_code = R"shd(
    #version 330 core 
    layout(location = 0) in vec2 v_pos;
    uniform mat3 camera_transform;
    out vec2 uv;
    void main() {
        pix_pos = v_pos.xy;//(inverse(camera_transform)*vec3(v_pos.xy, 1.)).xy;
    	gl_Position = vec4(v_pos.xy, 0.5, 1.);
    }
)shd";
constexpr const char* light_display_shd_fragment_code = R"shd(
    #version 330 core 
    uniform sampler2D light_display_tex;
    in vec2 uv;
    out vec4 outcol;
    void main() {
        //vec2 size = vec2(textureSize(bacground_tex, 0));
        //TODO add light paletre
        outcol = texture(light_display_tex, uv); // texture(bacground_tex, fract((floor(pix_pos) + 0.5) / size));
    }
)shd";

#endif