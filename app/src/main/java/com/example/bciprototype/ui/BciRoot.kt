package com.example.bciprototype.ui

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Modifier
import com.example.bciprototype.BciViewModel

@Composable
fun BciRoot(viewModel: BciViewModel) {
    val engineState = viewModel.engineState.collectAsState()
    val cursorState = viewModel.cursorState.collectAsState()

    Box(modifier = Modifier.fillMaxSize()) {
        CursorView(
            cursorX = cursorState.value.x,
            cursorY = cursorState.value.y
        )
        DebugPanel(
            engineState = engineState.value.name,
            cursorX = cursorState.value.x,
            cursorY = cursorState.value.y
        )
    }
}
