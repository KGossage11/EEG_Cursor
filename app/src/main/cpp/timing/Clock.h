#pragma once

/*
Defines the monotonic clock interface
Used for "now" timing
*/

#include <cstdint>
#include <chrono>

class Clock {
public:
    static int64_t nowMicroseconds();
};