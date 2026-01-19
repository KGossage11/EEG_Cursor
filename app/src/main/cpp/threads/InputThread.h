#pragma once

/*
Defines the interface for the input acquisition thread.
This thread is responsible only for acquiring raw EEG samples
and writing them into the ring buffer.
*/

#include <thread>
#include <atomic>

#include "buffers/RingBuffer.h"
#include "buffers/EEGSample.h"

class InputThread {
public:
    explicit InputThread(RingBuffer<EEGSample>& buffer);
    ~InputThread();

    void start();
    void stop();

private:
    void run();
    RingBuffer<EEGSample>& buffer_;
    std::atomic<bool> running_;
    std::thread thread_;
};