package com.example.bciprototype

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.ui.Modifier
import com.example.bciprototype.ui.BciRoot
import com.example.bciprototype.ui.theme.BCIPrototypeTheme

class MainActivity : ComponentActivity() {

    private val viewModel: BciViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            BCIPrototypeTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    BciRoot(viewModel)
                }
            }
        }

        viewModel.initialize()
        viewModel.start()
    }
}
