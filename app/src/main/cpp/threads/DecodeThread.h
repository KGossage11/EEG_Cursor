#pragma once

/*
Defines the interface for the decode thread.
This thread runs at a fixed cadence, extracts a bounded decode window,
produces an intent, and writes it to a latest-value intent buffer.
The thread is timing-budget aware.
*/

#include <atomic>
#include <thread>

#include "../buffers/RingBuffer.h"
#include "../buffers/DecodeWindow.h"
#include "../buffers/IntentBuffer.h"
#include "../buffers/EegSample.h"
#include "CursorIntent.h"

class DecodeThread {
public:
    DecodeThread(RingBuffer<EegSample>& inputBuffer, IntentBuffer<CursorIntent>& intentBuffer);
    ~DecodeThread();

    void start();
    void stop();

private:
    void run();
    RingBuffer<EegSample>& inputBuffer_;
    IntentBuffer<CursorIntent>& intentBuffer_;
    std::atomic<bool> running_;
    std::thread thread_;
};