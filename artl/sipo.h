
#pragma once

#include <stdint.h>

namespace artl {

template<typename VALUE_TYPE, typename BIT_ORDER,
         typename DATA_PIN, typename LATCH_PIN, typename CLOCK_PIN>
struct sipo {
    using value_type = VALUE_TYPE;
    using bit_order = BIT_ORDER;
    using data = DATA_PIN;   /* aka DS */
    using latch = LATCH_PIN; /* aka ST_CP */
    using clock = CLOCK_PIN; /* aka SH_CP */

    void setup() {
        data().output();
        latch().output();
        clock().output();

        latch().high();
    }

    struct write_bit {
        void operator()(bool b) const {
            data().write(b);

            clock().high();
            clock().low();
        }
    };

    void write(value_type v) const {
        latch().low();

        bit_order().write( v, write_bit() );
        latch().high();
    }

};

}
