
#pragma once

#include <stdint.h>

namespace artl {

template<typename VALUE_TYPE, typename BIT_ORDER,
         typename QH_PIN, typename LD_PIN, typename CLK_PIN>
struct piso {
    using value_type = VALUE_TYPE;
    using bit_order = BIT_ORDER;
    using qh = QH_PIN;
    using ld = LD_PIN;
    using clk = CLK_PIN;

    void setup() {
        qh().input();

        ld().output();
        ld().high();

        clk().output();
        clk().low();
    }

    struct read_bit {
        uint8_t operator()() const {
            uint8_t res = qh().read();

            clk().high();
            clk().low();

            return res;
        }
    };

    value_type read() const {
        ld().low();
        ld().high();

        value_type tmp;
        bit_order().read( tmp, read_bit() );

        return tmp;
    }

};

}
