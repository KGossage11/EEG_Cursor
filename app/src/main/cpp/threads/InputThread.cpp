/*
Implements the EEG acquisition thread.
This thread continuously acquires samples and writes them into
the ring buffer. It performs no decoding and no output logic.
*/

#include "InputThread.h"
#include "../timing/Clock.h"

#include <fstream>
#include <chrono>
#include <thread>

static constexpr const char* EEG_FILE_PATH = "/data/local/tmp/eeg_samples.csv";

InputThread::InputThread(RingBuffer<EegSample>& buffer)
    : buffer_(buffer), running_(false) {}

InputThread::~InputThread() {
    stop();
}

void InputThread::start() {
    running_ = true;
    thread_ = std::thread(&InputThread::run, this);
}

void InputThread::stop() {
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void InputThread::run() {
    std::ifstream file(EEG_FILE_PATH);
    if (!file.is_open()) {
        return;
    }

    while (running_) {
        EegSample sample{};
        sample.timestamp_us = Clock::nowMicroseconds();

        for (int i = 0; i < 8; ++i) {
            if (!(file >> sample.channels[i])) {
                return;
            }
        }

        buffer_.push(sample);
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
}