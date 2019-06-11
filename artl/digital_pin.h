
#pragma once

#include <stdint.h>
#include "bits/pin_traits.h"

namespace artl {

template<uint8_t PIN_NO, typename TRAITS = pin_traits<PIN_NO> >
struct digital_pin {

    enum {
        pin = PIN_NO
    };

    using traits = TRAITS;


    void output() const { traits().output(); }

    void input() { traits().input(); }


    void high() const { traits().high(); }

    void low() const { traits().low(); }

    void write(bool v) const { traits().write(v); }

    bool read() { return traits().read(); }

    uint8_t read_bit() { return traits().read_bit(); }


    constexpr operator uint8_t() const { return PIN_NO; }
};

}
