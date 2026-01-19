#pragma once

/*
NativeStateMachine is the sole authority over the native system lifecycle.

Responsibilities:
- Own the current NativeState
- Enforce legal state transitions
- Provide a single source of truth for lifecycle queries

This class does NOT:
- Allocate or free memory
- Start or stop threads
- Perform I/O
- Contain Android or JNI logic

Invalid transitions must fail explicitly and predictably.
*/

#include "NativeState.h"

class NativeStateMachine {
public:
    NativeStateMachine();

    NativeState currentState() const;

    bool initialize();
    bool start();
    bool pause();
    bool stop();

    bool canInitialize() const;
    bool canStart() const;
    bool canPause() const;
    bool canStop() const;
private:
    NativeState state_;
};
