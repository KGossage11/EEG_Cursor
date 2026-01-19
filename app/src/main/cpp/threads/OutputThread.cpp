/*
Implements the output thread.
This thread continuously reads the latest intent and produces
stable output with no backlog or queueing behavior.
*/

#include "OutputThread.h"

OuputThread::OutputThread(IntentBuffer<int>& intentBuffer)
    : intentBuffer_(intentBuffer), running_(false) {}

OuputThread::~OuputThread() {
    stop();
}

void Outputthread::start() {
    running_ = true;
    thread_ = std::thread(&OutputThread::run, this)
}

void OutputThread::stop() {
    running_ = false;
    if(thread_.joinable()) {
        thread_.join();
    }
}

woid Outputthread::run() {
    while(running_) {
        int intent;
        if (intentbuffer_.read(intent)){
            // Process the intent to produce stable output
            // (Implementation of output processing goes here)
        }
    }
}