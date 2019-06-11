
#include "artl/digital_in.h"
#include "artl/digital_out.h"
#include "artl/pin_change_int.h"
#include "artl/yield.h"

#define HAVE_HWSERIAL

#include "debug.h"

using sensor_in = artl::digital_in<10>;
using sensor_int = artl::pin_change_int<sensor_in::pin>;
using relay_out = artl::digital_out<9>;

bool sensor_state;
bool new_sensor_state;
unsigned long relay_on_ms = 0;

const unsigned long min_period_ms = 100;

#if defined(ISR) && defined(PCINT0_vect)
ISR(PCINT0_vect) {
    new_sensor_state = sensor_in().read();
}
#endif

void setup() {
#if defined(HAVE_HWSERIAL)
    Serial.begin(115200);
#endif

    sensor_in().setup();
    relay_out().setup();

    sensor_int().enable();

    sensor_state = sensor_in().read();
    new_sensor_state = sensor_state;

    artl::yield();
}

void loop() {
    unsigned long t = millis();

    if (new_sensor_state != sensor_state) {
        sensor_state = new_sensor_state;

        if (sensor_state) {
            if (t - relay_on_ms > min_period_ms) {
                relay_out().high();

                relay_on_ms = t;
            } else {
                debug("skip pulse ", t - relay_on_ms);
            }
        } else {
            relay_out().low();
        }
    }

    artl::yield();
}
