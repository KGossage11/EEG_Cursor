/*
Implements the fixed-period decode thread.
This thread executes decoding work on a strict cadence, enforces
execution time budgets, and skips work when deadlines are missed.
*/

#include "DecodeThread.h"
#include "../timing/Clock.h"
#include "../timing/TimingBudget.h"

#include <thread>

DecodeThread::DecodeThread(RingBuffer<EegSample>& inputBuffer, IntentBuffer<int>& intentBuffer)
    : inputBuffer_(inputBuffer), intentBuffer_(intentBuffer), running_(false) {}

DecopdeThread::~DecodeThread() {
    stop();
}

void DecodeThread::start() {
    running_ = true;
    thread_ = std::thread(&DecodeThread::run, this);
}

void DecodeThread::stop() {
    running_ = false;
    if(thread_.joinable()) {
        thread_.join();
    }
}

void DecodeThread::run() {
    const int64_t periodMicroseconds = TimingBudget::DecodePeriodMicroseconds();
    while(running_) { 
        int64_t startTime = Clock::nowMicroseconds();
        EegSample latest;
        if (inputbuffer_.readLatest(latest)) {
            DecodeWindow window{&latest, 1};

            int intent = 0;
            intentBuffer_.write(intent);
        }

        int64_t executionTime = Clock::nowMicroseconds() - startTime;

        if (TimingBudget::isDeadlineMiss(executionTime)) {
            continue;
        }

        int64_t sleepTime = periodMicroseconds - executionTime;
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
        }
    }
}