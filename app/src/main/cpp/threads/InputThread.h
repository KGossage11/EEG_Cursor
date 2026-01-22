#pragma once

/*
Defines the interface for the input acquisition thread.
This thread is responsible only for acquiring raw EEG samples
and writing them into the ring buffer.
*/

#include <thread>
#include <atomic>

#include "../buffers/RingBuffer.h"
#include "../buffers/EegSample.h"

class InputThread {
public:
    explicit InputThread(RingBuffer<EegSample>& buffer);
    ~InputThread();

    void start();
    void stop();

private:
    void run();
    RingBuffer<EegSample>& buffer_;
    std::atomic<bool> running_;
    std::thread thread_;
};