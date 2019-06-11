
#pragma once

#include <stdint.h>

namespace artl {

template<typename PORT>
struct port_traits {
};

template<uint8_t PIN_NO>
struct pin_traits {
    void input() const { pinMode(PIN_NO, INPUT); }

    void output() const { pinMode(PIN_NO, OUTPUT); }

    bool read() const { return digitalRead(PIN_NO) == HIGH; }

    void write(bool v) const { digitalWrite(PIN_NO, v ? HIGH : LOW); }

    void high() const { digitalWrite(PIN_NO, HIGH); }

    void low() const { digitalWrite(PIN_NO, LOW); }
};

template<typename PORT, uint8_t BIT_NO, typename BIT_MASK_TYPE = uint8_t>
struct base_pin_traits {

    using port = port_traits<PORT>;
    using bit_mask_t = BIT_MASK_TYPE;

    constexpr static bit_mask_t bit_mask = 1UL << BIT_NO;
    constexpr static uint8_t bit_no = BIT_NO;

    void input() const { port().dir() &= ~bit_mask; }

    void output() const { port().dir() |= bit_mask; }

    bool read() const {
        return read_bit() != 0;
    }

    bit_mask_t read_bit() const {
        return port().in() & bit_mask;
    }

    void write(bool v) const {
        if (v) {
            high();
        } else {
            low();
        }
    }

    void high() const { port().out() |= bit_mask; }

    void low() const { port().out() &= ~bit_mask; }
};

}

#if defined(ARDUINO_ARCH_AVR)
#include "variants/avr/port_traits.h"
#endif

#if defined(ARDUINO_ARCH_ESP32)
#include "variants/esp32/port_traits.h"

#include "variants/esp32/pin_traits.h"
#endif

#ifdef ARDUINO_AVR_LEONARDO
#include "variants/leonardo/pin_traits.h"
#endif

#if defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_UNO)
#include "variants/standard/pin_traits.h"
#endif

#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
#include "variants/tiny14/pin_traits.h"
#endif

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#include "variants/tiny8/pin_traits.h"
#endif

