package com.bjornsundin.save_him

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.content.ContextCompat
import com.google.android.material.button.MaterialButton

class GameOver : AppCompatActivity() {
    fun makeManHappy(p_viewID: Int) {
        findViewById<ImageView>(p_viewID).apply {
            setImageDrawable(ContextCompat.getDrawable(applicationContext, R.drawable.happy_man))
            (layoutParams as ConstraintLayout.LayoutParams).bottomMargin = 160f.px
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.game_over)

        // Change some of the layout if the player won
        if (intent.getBooleanExtra(MESSAGE_PLAYER_WON, false)) {
            makeManHappy(R.id.imageView_leftMan)
            makeManHappy(R.id.imageView_rightMan)

            findViewById<TextView>(R.id.text_gameOverTitle).apply {
                text = getString(R.string.you_saved_him)
                setTextColor(ContextCompat.getColor(applicationContext, R.color.green))
            }
            findViewById<TextView>(R.id.text_diappointed).apply {
                text = getString(R.string.thank_you)
                setTextColor(ContextCompat.getColor(applicationContext, R.color.green))
            }
        }

        findViewById<MaterialButton>(R.id.button_tryAgain).setOnClickListener {
            finish()
            startActivity(Intent(applicationContext, Game::class.java).apply {
                putExtra(MESSAGE_DIFFICULTY_MEAN, intent.getFloatExtra(MESSAGE_DIFFICULTY_MEAN, 0.5f))
                putExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, intent.getFloatExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, 0.5f))
            })
            overridePendingTransition(0, 0)
        }
        findViewById<MaterialButton>(R.id.button_changeDifficulty).setOnClickListener {
            finish() // Should go back to the change difficulty screen
            overridePendingTransition(0, 0)
        }
        findViewById<MaterialButton>(R.id.button_home).setOnClickListener {
            finish()
            startActivity(Intent(applicationContext, StartScreen::class.java).apply { flags = Intent.FLAG_ACTIVITY_CLEAR_TASK or Intent.FLAG_ACTIVITY_NEW_TASK })
            overridePendingTransition(0, 0)
        }
    }
}
