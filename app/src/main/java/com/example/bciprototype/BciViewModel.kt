package com.example.bciprototype

import com.example.bciprototype.lifecycle.NativeBridge
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch

enum class EngineState {
    UNINITIALIZED,
    INITIALIZED,
    RUNNING,
    PAUSED,
    STOPPED
}

data class CursorState(
    val x: Float = 0f,
    val y: Float = 0f
)

class BciViewModel : ViewModel() {

    private val bridge = NativeBridge()

    private val _engineState = MutableStateFlow(EngineState.UNINITIALIZED)
    val engineState: StateFlow<EngineState> = _engineState

    private val _cursorState = MutableStateFlow(CursorState())
    val cursorState: StateFlow<CursorState> = _cursorState

    fun initialize() {
        viewModelScope.launch {
            val ok = bridge.nativeInitialize()
            _engineState.value = if (ok) EngineState.INITIALIZED else EngineState.UNINITIALIZED
        }
    }

    fun start() {
        viewModelScope.launch {
            val ok = bridge.nativeStart()
            _engineState.value = if (ok) EngineState.RUNNING else _engineState.value
        }
    }

    fun pause() {
        viewModelScope.launch {
            val ok = bridge.nativePause()
            _engineState.value = if (ok) EngineState.PAUSED else _engineState.value
        }
    }

    fun stop() {
        viewModelScope.launch {
            val ok = bridge.nativeStop()
            _engineState.value = if (ok) EngineState.STOPPED else _engineState.value
        }
    }

    fun updateCursor(x: Float, y: Float) {
        _cursorState.value = CursorState(x, y)
    }
}
