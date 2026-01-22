/*
Implements Android logging helpers.
This file isolates all Android-specific includes and symbols.
*/

#include "AndroidLog.h"

#ifdef __ANDROID__
#include <android/log.h>
#endif

namespace AndroidLog {

    void info(const char* tag, const char* msg) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_INFO, tag, "%s", msg);
#endif
    }

    void error(const char* tag, const char* msg) {
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_ERROR, tag, "%s", msg);
#endif
    }
}
