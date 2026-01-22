/*
Implements JNI bindings for the native BCI engine.
This file contains no business logic and delegates all behavior
to NativeStateMachine and BciEngine.
*/

#include <jni.h>

#include "native_api.h"

#include "../state/NativeStateMachine.h"
#include "../core/BciEngine.h"

static NativeStateMachine gStateMachine;
static BciEngine* gEngine = nullptr;

namespace NativeApi {

    bool initialize() {
        if (!gStateMachine.initialize()) {
            return false;
        }

        if (gEngine == nullptr) {
            gEngine = new BciEngine(gStateMachine);
        }

        return true;
    }

    bool start() {
        if (!gEngine) {
            return false;
        }

        gEngine->start();
        return true;
    }

    bool pause() {
        if (!gEngine) {
            return false;
        }

        return gStateMachine.pause();
    }

    bool stop() {
        if (!gEngine) {
            return false;
        }

        gEngine->stop();
        return true;
    }
}

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_example_bciprototype_lifecycle_NativeBridge_nativeInitialize(
        JNIEnv*, jobject) {
    return NativeApi::initialize() ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_example_bciprototype_lifecycle_NativeBridge_nativeStart(
        JNIEnv*, jobject) {
    return NativeApi::start() ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_example_bciprototype_lifecycle_NativeBridge_nativePause(
        JNIEnv*, jobject) {
    return NativeApi::pause() ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_example_bciprototype_lifecycle_NativeBridge_nativeStop(
        JNIEnv*, jobject) {
    return NativeApi::stop() ? JNI_TRUE : JNI_FALSE;
}

}

