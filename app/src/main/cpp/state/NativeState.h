#pragma once

/*
NativeState defines the possible states of the native system

Each state encodes strict guarantees about:
- What memory exists
- What threads may be running
- What operations are legal

States:
UNINITIALIZED
- No native resources exist
- No memory allocated
- No threads created
- Valid actions: initialize

INITIALIZED
- All buffers and core objects are allocated
- No threads are running
- Safe point before real-time execution
- Valid actions: start, stop

RUNNING
- Threads are actively executing
- No allocation or deallocation allowed
- All timing guarantees must be enforced
- Valid actions: pause, stop

PAUSED
- Threads are stopped or sleeping
- Memory and state are preserved
- Allows fast resume without reallocation
- Valid actions: start (resume), stop

STOPPED
- Threads are fully shut down and joined
- Memory is released
- System is cleanly torn down
- Valid actions: initialize (optional restart)
*/


enum class NativeState {
    UNINITIALIZED,
    INITIALIZED,
    RUNNING,
    PAUSED,
    STOPPED,
    COUNT
};