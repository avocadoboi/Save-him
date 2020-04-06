package com.bjornsundin.save_him

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.google.android.material.button.MaterialButton

class GameOver : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.game_over)

        findViewById<MaterialButton>(R.id.button_tryAgain).setOnClickListener {
            startActivity(Intent(applicationContext, Game::class.java).apply {
                putExtra(MESSAGE_DIFFICULTY_MEAN, intent.getFloatExtra(MESSAGE_DIFFICULTY_MEAN, 0.5f))
                putExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, intent.getFloatExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, 0.5f))
            })
            finish()
            overridePendingTransition(0, 0)
        }
        findViewById<MaterialButton>(R.id.button_changeDifficulty).setOnClickListener {
            finish() // Should go back to the change difficulty screen
            overridePendingTransition(0, 0)
        }
        findViewById<MaterialButton>(R.id.button_home).setOnClickListener {
            startActivity(Intent(applicationContext, StartScreen::class.java).apply { flags = Intent.FLAG_ACTIVITY_CLEAR_TASK or Intent.FLAG_ACTIVITY_NEW_TASK })
            finish()
            overridePendingTransition(0, 0)
        }
    }
}
