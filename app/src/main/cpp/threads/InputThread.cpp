/*
Implements the EEG acquisition thread.
This thread continuously acquires samples and writes them into
the ring buffer. It performs no decoding and no output logic.
*/

#include "InputThread.h"
#include "../timing/Clock.h"

InputThread::InputThread(RingBuffer<EegSample>& buffer)
    : buffer_(buffer), running_(false) {}

InputThread::~InputThread() {
    stop();
}

void InputThread::start() {
    running_ = true;
    thread_ = std::thread(&InputThread::run, this);
}

void Inputthread::stop() {
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void InputThread::run() {
    while (running_) {
        EegSample sample{};
        sample.timestamp = Clock::nowMicroseconds();

        for (int i = 0; i < 8; ++i) {
            sample.channels[i] = 0.0f; // placeholder loop depending on actual data source
        }

        buffer_.push(sample);
    }
}