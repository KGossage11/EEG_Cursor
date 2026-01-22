#pragma once

/*
Defines the top-level orchestration engine for the BCI system.
This class owns all threads and buffers and provides lifecycle-safe
start and stop operations. No platform or JNI logic exists here.
*/

#include "../state/NativeStateMachine.h"

#include "../buffers/RingBuffer.h"
#include "../buffers/EegSample.h"
#include "../buffers/IntentBuffer.h"

#include "../threads/InputThread.h"
#include "../threads/DecodeThread.h"
#include "../threads/OutputThread.h"

#include "../threads/CursorIntent.h"

class BciEngine {
public:
    explicit BciEngine(NativeStateMachine& stateMachine);
    ~BciEngine();

    void start();
    void stop();

private:
    NativeStateMachine& stateMachine_;
    
    RingBuffer<EegSample> eegBuffer_;
    IntentBuffer<CursorIntent> intentBuffer_;

    InputThread inputThread_;
    DecodeThread decodeThread_;
    OutputThread outputThread_;
    bool running_;
};