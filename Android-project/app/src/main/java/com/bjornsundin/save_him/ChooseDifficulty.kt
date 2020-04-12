package com.bjornsundin.save_him

import android.content.Intent
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.google.android.material.button.MaterialButton
import com.google.android.material.slider.Slider

const val MESSAGE_DIFFICULTY_MEAN = "MESSAGE_DIFFICULTY_MEAN"
const val MESSAGE_DIFFICULTY_STANDARD_DEVIATION = "MESSAGE_DIFFICULTY_STANDARD_DEVIATION"

class ChooseDifficulty : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.choose_difficulty)

        findViewById<MaterialButton>(R.id.button_saveTheMan).setOnClickListener {
            startActivity(Intent(this, Game::class.java).apply {
                putExtra(MESSAGE_DIFFICULTY_MEAN, findViewById<Slider>(R.id.slider_mean).value)
                putExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, findViewById<Slider>(R.id.slider_standardDeviation).value)
            })
            overridePendingTransition(0, 0)
        }
    }
}