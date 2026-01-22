package com.example.bciprototype.lifecycle

/*
Defines the Kotlin bridge to native code.
This file contains only external declarations and simple
lifecycle-to-native mappings.
*/

class NativeBridge {

    external fun nativeInitialize(): Boolean
    external fun nativeStart(): Boolean
    external fun nativePause(): Boolean
    external fun nativeStop(): Boolean

    fun onCreate(): Boolean {
        return nativeInitialize()
    }

    fun onStart(): Boolean {
        return nativeStart()
    }

    fun onPause(): Boolean {
        return nativePause()
    }

    fun onStop(): Boolean {
        return nativeStop()
    }

    companion object {
        init {
            System.loadLibrary("bci_native")
        }
    }
}

