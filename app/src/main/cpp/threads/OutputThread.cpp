/*
Implements the output thread.
This thread continuously reads the latest intent and produces
stable output with no backlog or queueing behavior.
*/

#include "OutputThread.h"
#include "CursorIntent.h"

#include <thread>
#include <algorithm>

OutputThread::OutputThread(
        IntentBuffer<CursorIntent>& intentBuffer)
        : intentBuffer_(intentBuffer),
          running_(false),
          cursorX_(0.0f),
          cursorY_(0.0f) {}

OutputThread::~OutputThread() {
    stop();
}

void OutputThread::start() {
    running_ = true;
    thread_ = std::thread(&OutputThread::run, this);
}

void OutputThread::stop() {
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void OutputThread::run() {
    while (running_) {
        CursorIntent intent;
        if (intentBuffer_.read(intent)) {

            cursorX_ += intent.dx * 0.01f;
            cursorY_ += intent.dy * 0.01f;

            cursorX_ = std::clamp(cursorX_, -1.0f, 1.0f);
            cursorY_ = std::clamp(cursorY_, -1.0f, 1.0f);
        }
    }
}
