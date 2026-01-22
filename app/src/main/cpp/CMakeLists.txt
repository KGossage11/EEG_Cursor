cmake_minimum_required(VERSION 3.22.1)

project(bci_native)

add_library(
        bci_native
        SHARED

        entry/jni_entry.cpp

        state/NativeStateMachine.cpp

        core/BciEngine.cpp

        platform/AndroidLog.cpp

        threads/InputThread.cpp
        threads/DecodeThread.cpp
        threads/OutputThread.cpp

        timing/Clock.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        bci_native
        ${log-lib}
)
