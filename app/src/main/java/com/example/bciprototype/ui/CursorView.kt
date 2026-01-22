package com.example.bciprototype.ui

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color

@Composable
fun CursorView(
    cursorX: Float,
    cursorY: Float,
    modifier: Modifier = Modifier
) {
    Canvas(modifier = modifier.fillMaxSize()) {
        val centerX = size.width / 2f
        val centerY = size.height / 2f

        val dotX = centerX + cursorX * (size.width / 2f)
        val dotY = centerY - cursorY * (size.height / 2f)

        drawCircle(
            color = Color.Red,
            radius = 10f,
            center = Offset(dotX, dotY)
        )
    }
}
