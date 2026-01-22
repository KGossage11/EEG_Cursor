#pragma once

/*
Defines a platform-agnostic logging interface.
This header isolates logging usage from any Android or JNI headers.
Actual platform binding is performed elsewhere.
*/

namespace AndroidLog {

    void info(const char* tag, const char* msg);
    void error(const char* tag, const char* msg);
}
