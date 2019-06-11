
#pragma once

#include <stdint.h>
#include <avr/io.h>

namespace artl {

struct port {
    struct A { };
    struct B { };
    struct C { };
    struct D { };
    struct E { };
    struct F { };
};

#ifdef DDRA

template<>
struct port_traits<port::A> {
    volatile uint8_t& dir() { return DDRA; }
    uint8_t in() { return PINA; }
    volatile uint8_t& out() { return PORTA; }
};

#endif

#ifdef DDRB

template<>
struct port_traits<port::B> {
    volatile uint8_t& dir() { return DDRB; }
    uint8_t in() { return PINB; }
    volatile uint8_t& out() { return PORTB; }
};

#endif

#ifdef DDRC

template<>
struct port_traits<port::C> {
    volatile uint8_t& dir() { return DDRC; }
    uint8_t in() { return PINC; }
    volatile uint8_t& out() { return PORTC; }
};

#endif

#ifdef DDRD

template<>
struct port_traits<port::D> {
    volatile uint8_t& dir() { return DDRD; }
    uint8_t in() { return PIND; }
    volatile uint8_t& out() { return PORTD; }
};

#endif

#ifdef DDRE

template<>
struct port_traits<port::E> {
    volatile uint8_t& dir() { return DDRE; }
    uint8_t in() { return PINE; }
    volatile uint8_t& out() { return PORTE; }
};

#endif

#ifdef DDRF

template<>
struct port_traits<port::F> {
    volatile uint8_t& dir() { return DDRF; }
    uint8_t in() { return PINF; }
    volatile uint8_t& out() { return PORTF; }
};

#endif

}
