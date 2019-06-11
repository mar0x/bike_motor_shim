
#pragma once

#include <stdint.h>
#include <soc/gpio_reg.h>

namespace artl {

struct port {
    struct GPIO { };
    struct GPIO1 { };
};

template<>
struct port_traits<port::GPIO> {
    volatile uint32_t& dir() { return * (volatile uint32_t*)(GPIO_ENABLE_REG); }
    uint32_t in() { return * (volatile uint32_t*)(GPIO_IN_REG); }
    volatile uint32_t& out() { return * (volatile uint32_t*)(GPIO_OUT_REG); }
};

template<>
struct port_traits<port::GPIO1> {
    volatile uint32_t& dir() { return * (volatile uint32_t*)(GPIO_ENABLE1_REG); }
    uint32_t in() { return * (volatile uint32_t*)(GPIO_IN1_REG); }
    volatile uint32_t& out() { return * (volatile uint32_t*)(GPIO_OUT1_REG); }
};

}
