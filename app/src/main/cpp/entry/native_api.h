#pragma once

/*
Defines the native C++ API exposed to JNI.
This interface contains no JNI types and no platform dependencies.
*/

namespace NativeApi {

    bool initialize();
    bool start();
    bool pause();
    bool stop();
}
