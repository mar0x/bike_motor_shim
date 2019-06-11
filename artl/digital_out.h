
#pragma once

#include <stdint.h>

#include "bits/pin_traits.h"

namespace artl {

template<uint8_t PIN_NO, typename PIN_TRAITS = pin_traits<PIN_NO> >
struct digital_out {

    enum {
        pin = PIN_NO
    };

    using traits = PIN_TRAITS;

    void setup() const { traits().output(); }

    void output() const { traits().output(); }

    void high() const { traits().high(); }

    void low() const { traits().low(); }

    void write(bool v) const { traits().write(v); }

    constexpr operator uint8_t() const { return PIN_NO; }
};

}
