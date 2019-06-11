
#pragma once

#include <stdint.h>
#include "bits/pin_change_traits.h"

#if !defined(PCICR) && defined(GIMSK)
#define PCICR GIMSK
#endif

namespace artl {

template<uint8_t PIN_NO, typename TRAITS = pin_change_traits<PIN_NO> >
struct pin_change_int {

    using traits = TRAITS;

    void enable() const {
        icr_enable();
        traits().enable();
    }

    void disable() const { traits().disable(); }

    void icr_enable() const { PCICR |= traits::icr_bit_mask; }

    void icr_disable() const { PCICR &= ~traits::icr_bit_mask; }
};

}
