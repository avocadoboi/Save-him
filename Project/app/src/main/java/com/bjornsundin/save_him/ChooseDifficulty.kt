package com.bjornsundin.save_him

import android.content.Intent
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.google.android.material.slider.Slider

const val MESSAGE_DIFFICULTY_MEAN = "mean"
const val MESSAGE_DIFFICULTY_STANDARD_DEVIATION = "standard deviation"

class ChooseDifficulty : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.choose_difficulty)
    }

    fun saveTheMan(p_view: View) {
        startActivity(Intent(this, Game::class.java).apply {
            putExtra(MESSAGE_DIFFICULTY_MEAN, findViewById<Slider>(R.id.slider_mean).value)
            putExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, findViewById<Slider>(R.id.slider_standardDeviation).value)
        })
    }
}