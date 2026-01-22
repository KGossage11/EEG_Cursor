/*
Implements the fixed-period decode thread.
This thread executes decoding work on a strict cadence, enforces
execution time budgets, and skips work when deadlines are missed.
*/

#include "DecodeThread.h"
#include "../timing/Clock.h"
#include "../timing/TimingBudget.h"
#include "CursorIntent.h"

#include <thread>
#include <algorithm>
#include <cmath>

DecodeThread::DecodeThread(RingBuffer<EegSample>& inputBuffer, IntentBuffer<CursorIntent>& intentBuffer)
    : inputBuffer_(inputBuffer), intentBuffer_(intentBuffer), running_(false) {}

DecodeThread::~DecodeThread() {
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
    const int64_t periodMicroseconds = TimingBudget::DecodePeriodMicroseconds;
    while(running_) { 
        int64_t startTime = Clock::nowMicroseconds();

        EegSample sample;
        if (inputBuffer_.readLatest(sample)) {

            float dx = 0.0f;
            float dy = 0.0f;

            for (int i = 0; i < 4; ++i) {
                dx += sample.channels[i];
            }
            for (int i = 4; i < 8; ++i) {
                dy += sample.channels[i];
            }

            dx *= 0.25f;
            dy *= 0.25f;

            CursorIntent intent;
            intent.dx = dx;
            intent.dy = dy;
            intent.confidence = std::min(1.0f, std::abs(dx) + std::abs(dy));

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