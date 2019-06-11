
#pragma once

#include <stdint.h>
#include <soc/gpio_reg.h>

namespace artl {

template<>
struct pin_traits<0> : public base_pin_traits<port::GPIO, 0, uint32_t> { };

template<>
struct pin_traits<1> : public base_pin_traits<port::GPIO, 1, uint32_t> { };

template<>
struct pin_traits<2> : public base_pin_traits<port::GPIO, 2, uint32_t> { };

template<>
struct pin_traits<3> : public base_pin_traits<port::GPIO, 3, uint32_t> { };

template<>
struct pin_traits<4> : public base_pin_traits<port::GPIO, 4, uint32_t> { };

template<>
struct pin_traits<5> : public base_pin_traits<port::GPIO, 5, uint32_t> { };

template<>
struct pin_traits<6> : public base_pin_traits<port::GPIO, 6, uint32_t> { };

template<>
struct pin_traits<7> : public base_pin_traits<port::GPIO, 7, uint32_t> { };

template<>
struct pin_traits<8> : public base_pin_traits<port::GPIO, 8, uint32_t> { };

template<>
struct pin_traits<9> : public base_pin_traits<port::GPIO, 9, uint32_t> { };

template<>
struct pin_traits<10> : public base_pin_traits<port::GPIO, 10, uint32_t> { };

template<>
struct pin_traits<21> : public base_pin_traits<port::GPIO, 21, uint32_t> { };

}
