#ifndef __gl_h_
#error "must be included after gl.h"
#endif

#include <string>
#include <map>

#include "id.hpp"

/*
    TODO add uniforms cahsing?
*/

class shader {
public:
    shader() {}
    shader(const std::string& vertex_code, const std::string& fragment_code) {
        //TODO add impl
    }
    static shader load_from_file(const std::string& vertex_file, const std::string& fragment_file) {
        //TODO add impl
    }

    static void unload_shader_by_id(unsigned id) {
        glDeleteProgram(id);
    }

    id_t<unload_shader_by_id> id;
};
