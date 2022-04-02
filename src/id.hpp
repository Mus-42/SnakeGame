#pragma once
#ifndef ID_INCLUDE_
#define ID_INCLUDE_
using destuct_f = void(unsigned);
using destuct_f_ptr = destuct_f*;
template<destuct_f f>
struct id_t {
    id_t(unsigned ID = 0) : id(ID) {}

    //no copy
    id_t(const id_t&) = delete;
    id_t& operator=(const id_t&) = delete;
    //move
    id_t(id_t&& o) : id(o.id) {
        o.id = 0;
    }
    id_t& operator=(id_t&& o) {
        if(id) f(id);//destruct ID
        id = o.id;
        o.id = 0;
        return *this;
    }

    ~id_t() {
        f(id);//destruct ID
    }

    operator unsigned() const {
        return id;
    }

    unsigned id;
};
#endif//ID_INCLUDE_