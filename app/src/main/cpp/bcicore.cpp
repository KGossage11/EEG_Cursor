/*
 Minimal native entry point to verify:
 - CMake wiring
 - NDK compilation
 - JNI symbol resolution
 - Native library loading
*/

#include <jni.h>
#include <android/log.h>

#define LOG_TAG "BCI_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_example_bciprototype_MainActivity_nativeInit(
        JNIEnv*,
jobject) {

LOGI("Native library loaded successfully");
}
