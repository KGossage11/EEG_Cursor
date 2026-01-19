#pramga once

// Defines a plain data structure representing a single EEG sample.

#include <cstdint>

struct EegSample {
    int64_t timestamp_us;
    float channels[8];
};