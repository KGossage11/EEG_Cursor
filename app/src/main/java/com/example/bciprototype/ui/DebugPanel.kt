package com.example.bciprototype.ui

import androidx.compose.foundation.layout.Column
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable

@Composable
fun DebugPanel(
    engineState: String,
    cursorX: Float,
    cursorY: Float
) {
    Column {
        Text(text = "Engine: $engineState")
        Text(text = "Cursor: x=$cursorX y=$cursorY")
    }
}
