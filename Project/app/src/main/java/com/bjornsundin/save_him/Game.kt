package com.bjornsundin.save_him

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import java.lang.Math
import java.util.Random
import kotlin.math.abs

class Game : AppCompatActivity() {
    private lateinit var m_words: List<String>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.game)

        val file = resources.openRawResource(R.raw.words)
        val reader = file.bufferedReader()
        m_words = reader.readLines()

        // Choose word
        val mean = intent.getFloatExtra(MESSAGE_DIFFICULTY_MEAN, 0.5f)
        val standardDeviation = 0.01 + 0.1f*intent.getFloatExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, 0.5f)

        val randomGenerator = Random()
        var index = (m_words.size*(randomGenerator.nextGaussian()*standardDeviation + mean)).toInt()
        index = if ((index / m_words.size) and 1 == 0) {
            abs(index % m_words.size)
        } else {
            abs(m_words.size - index % m_words.size - 1)
        }

        val word = m_words[index]
        findViewById<TextView>(R.id.text_test).text = index.toString() + ": " + word
    }
}
