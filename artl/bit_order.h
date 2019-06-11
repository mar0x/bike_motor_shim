
#pragma once

#include <stdint.h>

namespace artl {

struct lsb_first {

    template<typename F>
    void write(uint8_t v, const F& f) const {
        for(uint8_t i = 0; i < 8; i++) {
            f( (v & (1 << i)) != 0 );
        }
    }

    template<typename F>
    void write(uint16_t v, const F& f) const {
        write( (uint8_t) (v & 0xFF), f );
        write( (uint8_t) ((v >> 8) & 0xFF), f );
    }

    template<typename F>
    void read(uint8_t& v, const F& f) const {
        uint8_t tmp = 0;
        for(uint8_t i = 0; i < 8; i++) {
            if (f()) {
                tmp |= (1 << i);
            }
        }

        v = tmp;
    }

    template<typename F>
    void read(uint16_t& v, const F& f) const {
        uint8_t lo, hi;
        read(lo, f);
        read(hi, f);
        v = lo | (hi << 8);
    }

};


struct lsb_first_fast {

    template<typename F>
    void write(uint8_t v, const F& f) const {
        f( (v & 0x01u) != 0 );
        f( (v & 0x02u) != 0 );
        f( (v & 0x04u) != 0 );
        f( (v & 0x08u) != 0 );
        f( (v & 0x10u) != 0 );
        f( (v & 0x20u) != 0 );
        f( (v & 0x40u) != 0 );
        f( (v & 0x80u) != 0 );
    }

    template<typename F>
    void write(uint16_t v, const F& f) const {
        write( (uint8_t) ((v >> 8) & 0xFF), f );
        write( (uint8_t) (v & 0xFF), f );
    }

    template<typename F>
    void read(uint8_t& v, const F& f) const {
        v =
            f() |
            (f() << 1) |
            (f() << 2) |
            (f() << 3) |
            (f() << 4) |
            (f() << 5) |
            (f() << 6) |
            (f() << 7);
    }

    template<typename F>
    void read(uint16_t& v, const F& f) const {
        uint8_t lo, hi;
        read(lo, f);
        read(hi, f);
        v = lo | (hi << 8);
    }

};


struct msb_first {

    template<typename F>
    void write(uint8_t v, const F& f) const {
        for(uint8_t i = 7; i < 8; --i) {
            f( (v & (1 << i)) != 0 );
        }
    }

    template<typename F>
    void write(uint16_t v, const F& f) const {
        write( (uint8_t) ((v >> 8) & 0xFF), f );
        write( (uint8_t) (v & 0xFF), f );
    }

    template<typename F>
    void read(uint8_t& v, const F& f) const {
        uint8_t tmp = 0;

        for(uint8_t i = 7; i < 8; --i) {
            if (f()) {
                tmp |= (1 << i);
            }
        }

        v = tmp;
    }

    template<typename F>
    void read(uint16_t& v, const F& f) const {
        uint8_t lo, hi;
        read( hi, f );
        read( lo, f );
        v = lo | (hi << 8);
    }

};


struct msb_first_fast {

    template<typename F>
    void write(uint8_t v, const F& f) const {
        f( (v & 0x80u) != 0 );
        f( (v & 0x40u) != 0 );
        f( (v & 0x20u) != 0 );
        f( (v & 0x10u) != 0 );
        f( (v & 0x08u) != 0 );
        f( (v & 0x04u) != 0 );
        f( (v & 0x02u) != 0 );
        f( (v & 0x01u) != 0 );
    }

    template<typename F>
    void write(uint16_t v, const F& f) const {
        write( (uint8_t) ((v >> 8) & 0xFF), f );
        write( (uint8_t) (v & 0xFF), f );
    }

    template<typename F>
    void read(uint8_t& v, const F& f) const {
        v =
            (f() << 7) |
            (f() << 6) |
            (f() << 5) |
            (f() << 4) |
            (f() << 3) |
            (f() << 2) |
            (f() << 1) |
            f();
    }

    template<typename F>
    void read(uint16_t& v, const F& f) const {
        uint8_t lo, hi;
        read( hi, f );
        read( lo, f );
        v = lo | (hi << 8);
    }

};


}
