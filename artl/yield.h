
#pragma once

#include <avr/interrupt.h>
#include <avr/sleep.h>

namespace artl
{

inline void yield()
{
    sleep_enable();
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_cpu();
}

}
