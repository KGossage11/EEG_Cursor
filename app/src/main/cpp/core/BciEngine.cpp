/*
Implements lifecycle management and wiring for the BCI engine.
This file is responsible for constructing buffers, creating threads,
and ensuring safe startup and shutdown ordering.
*/

#include "BciEngine.h"
#include "../state/NativeStateMachine.h"

BciEngine::BciEngine(NativeStateMachine &stateMachine)
    : stateMachine_(stateMachine),
      eegBuffer_(256),
      intentBuffer_(),
      inputThread_(eegBuffer_),
      decodeThread_(eegBuffer_, intentBuffer_),
      outputThread_(intentBuffer_) {}

BciEngine::~BciEngine() {
    stop();
}

void BciEngine::start() {
    if (!stateMachine_.start()) return;

    inputThread_.start();
    decodeThread_.start();
    outputThread_.start();
}

void BciEngine::stop() {
    if (!stateMachine_.stop()) return;

    outputThread_.stop();
    decodeThread_.stop();
    inputThread_.stop();
}


