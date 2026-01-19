/*
This file contains:
-Constants for decode period 
-Maximum allowed execution time 
-Helper checks for deadline miss
All values expressed in microseconds.
*/

#pragma once

#include <cstdint>

namespace TimingBudget {

    static constexpr int64_t DecodePeriodMicroseconds = 10000; // 10 ms
    static constexpr int64_t MaxExecutionTimeMicroseconds = 3000; // 3 ms
    static constexpr int64_t DeadlineMissMicroseconds = 1000; // 1 ms

    inline bool isDeadlineMiss(int64_t executionTimeMicroseconds) {
        return executionTimeMicroseconds > MaxExecutionTimeMicroseconds;
    }

    inline bool isLate(int64_t executionTimeMicroseconds) {
        return executionTimeMicroseconds > (DecodePeriodMicroseconds - DeadlineMissMicroseconds);
    }
}