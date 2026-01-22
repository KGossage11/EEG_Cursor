#pragma once

/*
Defines the interface for the output thread.
This thread consumes the latest available intent and produces
stable output. No rendering, platform, or UI logic exists here.
*/

#include <atomic>
#include <thread>

#include "CursorIntent.h"
#include "../buffers/IntentBuffer.h"

class OutputThread {
public:
    OutputThread(IntentBuffer<CursorIntent>& intentBuffer);
    ~OutputThread();

    void start();
    void stop();

private:
    void run();

    IntentBuffer<CursorIntent>& intentBuffer_;
    std::atomic<bool> running_;
    std::thread thread_;
    float cursorX_;
    float cursorY_;
};