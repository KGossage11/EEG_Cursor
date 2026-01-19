#include "NativeState.h"
#include "NativeStateMachine.h"

/*
    Implements a finite state machine using a transition truth table
    The truth table defines which state transitions are allowed
    state_ holds the current NativeState
    Transition functions verify legality before changing state_
*/

static constexpr int STATE_COUNT =
    static_cast<int>(NativeState::COUNT);

static constexpr bool truthTable[STATE_COUNT][STATE_COUNT] = {
/* FROM \ TO            UNINIT INIT  RUN   PAUSE STOP */
    /* UNINITIALIZED */ {0,    1,    0,    0,    0},
    /* INITIALIZED   */ {0,    0,    1,    0,    1},
    /* RUNNING       */ {0,    0,    0,    1,    1},
    /* PAUSED        */ {0,    0,    1,    0,    1},
    /* STOPPED       */ {0,    1,    0,    0,    0}
};

static constexpr int toIndex(NativeState state) {
    return static_cast<int>(state);
}

NativeStateMachine::NativeStateMachine()
    : state_(NativeState::UNINITIALIZED) {}

NativeState NativeStateMachine::currentState() const {
    return state_;
}

bool NativeStateMachine::canInitialize() const {
    return truthTable[toIndex(state_)][toIndex(NativeState::INITIALIZED)];
}

bool NativeStateMachine::canStart() const {
    return truthTable[toIndex(state_)][toIndex(NativeState::RUNNING)];
}

bool NativeStateMachine::canPause() const {
    return truthTable[toIndex(state_)][toIndex(NativeState::PAUSED)];
}

bool NativeStateMachine::canStop() const {
    return truthTable[toIndex(state_)][toIndex(NativeState::STOPPED)];
}

bool NativeStateMachine::initialize() {
    if (!canInitialize())
        return false;

    state_ = NativeState::INITIALIZED;
    return true;
}

bool NativeStateMachine::start() {
    if (!canStart())
        return false;

    state_ = NativeState::RUNNING;
    return true;
}

bool NativeStateMachine::pause() {
    if (!canPause())
        return false;

    state_ = NativeState::PAUSED;
    return true;
}

bool NativeStateMachine::stop() {
    if (!canStop())
        return false;

    state_ = NativeState::STOPPED;
    return true;
}