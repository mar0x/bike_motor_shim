#pragma once

#if defined(HAVE_HWSERIAL)
template<typename T1> void debug(const T1& a1) {
    Serial.println(a1);
}

template<typename T1, typename ...Args> void debug(const T1& a1, Args... args) {
    Serial.print(a1);
    debug(args...);
}
#else
#define debug(...)
#endif

