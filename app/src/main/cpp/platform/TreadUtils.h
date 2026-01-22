#pragma once

/*
Defines platform-specific thread utilities such as naming and
priority hints.
*/

#include <thread>

#ifdef __ANDROID__
#include <pthread.h>
#endif

namespace ThreadUtils {

    inline void setThreadName(const char* name) {
#ifdef __ANDROID__
        pthread_setname_np(pthread_self(), name);
#endif
    }

    inline void setRealtimePriority() {
#ifdef __ANDROID__
        sched_param param{};
        param.sched_priority = 1;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
#endif
    }
}
