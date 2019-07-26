
#include "artl/digital_in.h"
#include "artl/digital_out.h"
#include "artl/digital_pin.h"
#include "artl/pin_change_int.h"
#include "artl/yield.h"
#include "artl/button.h"


#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define SENSOR_IN_PIN   1
#define TTL_OUT_PIN     0
#define RELAY_OUT_PIN   2
#else
#define HAVE_HWSERIAL
#define SENSOR_IN_PIN   10
#define TTL_OUT_PIN     8
#define RELAY_OUT_PIN   9
#endif

#include "debug.h"

#define MAX_SPEED_KM_H        24
#define WHEEL_SIZE_INCH       27.5

#define MAX_SPEED_MM_S        ( MAX_SPEED_KM_H * 1000 / 3.6 )
#define WHEEL_SIZE_MM         ( WHEEL_SIZE_INCH * 25.4 )
#define WHEEL_CIRC_MM         ( WHEEL_SIZE_MM * 3.14159265358 )
#define MAX_PULSE_FREQ        ( MAX_SPEED_MM_S / WHEEL_CIRC_MM )
#define MIN_PULSE_PERIOD_MS   ( 1000 / MAX_PULSE_FREQ )

const unsigned long min_period_ms = (unsigned long) MIN_PULSE_PERIOD_MS;

struct {
    using sensor_in = artl::digital_in<SENSOR_IN_PIN>;
    using sensor_int = artl::pin_change_int<sensor_in::pin>;

    unsigned long on_ms = 0;
    unsigned long pulse_ms = 0;

    bool state = false;
    bool pulse = false;

    artl::button<> debouncer;

    void setup() {
        sensor_in().setup();
        sensor_int().enable();
    }

    void on_change() {
    }

    void update(unsigned long t) {
        if (!debouncer.update(!sensor_in().read(), t)) {
            return;
        }

        bool new_state = debouncer.down();
        if (new_state == state) {
            return;
        }

        state = new_state;

        if (state) {
            pulse = true;

            on_ms = t;
        } else {
            if (t - on_ms > pulse_ms) {
                pulse_ms = t - on_ms;
            }
            if (pulse_ms == 0) {
                pulse_ms = 1;
            }
        }
    }
} sensor;

struct {
    using relay_out = artl::digital_out<RELAY_OUT_PIN>;
    using ttl_out = artl::digital_pin<TTL_OUT_PIN>;

    unsigned long on_ms = 0;

    bool state = false;

    void setup() {
        relay_out().setup();

        ttl_out().input();
    }

    void update(unsigned long t) {
        if (!state && (sensor.state || (sensor.pulse && sensor.pulse_ms)) && t - on_ms >= min_period_ms) {
            on(t);
            sensor.pulse = false;
        }

        if (state && sensor.pulse_ms && t - on_ms >= sensor.pulse_ms) {
            off();
            sensor.pulse_ms = 0;
        }
    }

    void on(unsigned long t) {
        relay_out().high();

        ttl_out().output();
        ttl_out().low();

        state = true;
        on_ms = t;
    }

    void off() {
        relay_out().low();

        ttl_out().input();

        state = false;
    }

} relay;


#if defined(ISR) && defined(PCINT0_vect)
ISR(PCINT0_vect) {
    sensor.on_change();
}
#endif

void setup() {
#if defined(HAVE_HWSERIAL)
    Serial.begin(115200);
#endif

    sensor.setup();
    relay.setup();

//    artl::yield();
}

void loop() {
    unsigned long t = millis();

    sensor.update(t);
    relay.update(t);

//    artl::yield();
}
