#include "Clock.h"

/*
Provides a monotonic time source backed by std::chrono::steady_clock.
*/

int64_t Clock::nowMicroseconds() {
    using namespace std::chrono;
    return duration_cast<microseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}