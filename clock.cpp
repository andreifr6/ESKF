//
// Created by mmaximo on 18/10/2015.
//

#include "clock.h"
#include <sys/time.h>

Clock::Clock() {
}

Clock::~Clock() {
}

double Clock::getTime() {
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}
