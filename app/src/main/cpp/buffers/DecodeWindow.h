#pragma once

/*
Defines a non-owning fixed-size view into a contiguous sequence
of EEG samples. This structure does not manage memory and assumes
the backing storage outlives the view.
*/

#include <cstddef>
#include "EegSample.h"

struct DecodeWindow {
    const EegSample* samples;
    size_t count;
};
