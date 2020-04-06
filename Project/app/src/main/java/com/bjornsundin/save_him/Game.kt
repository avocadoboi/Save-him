package com.bjornsundin.save_him

import android.content.Intent
import android.content.res.Resources
import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.widget.GridLayout
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.core.content.res.ResourcesCompat
import java.util.Random
import kotlin.math.abs
import kotlin.math.min

val Float.px: Int get() = (this * Resources.getSystem().displayMetrics.density + 0.5f).toInt()

class Game : AppCompatActivity() {
    companion object {
        const val ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        const val NUMBER_OF_FAILED_ATTEMPTS_BEFORE_DEATH = 5
    }

    fun chooseWord(): String {
        val words = resources.openRawResource(R.raw.words).bufferedReader().readLines()

        val mean = intent.getFloatExtra(MESSAGE_DIFFICULTY_MEAN, 0.5f)
        val standardDeviation = 0.01f + 0.2f*intent.getFloatExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, 0.5f)

        val randomGenerator = Random()
        var index = (words.size*(randomGenerator.nextGaussian()*standardDeviation + mean)).toInt()
        index = if ((index / words.size) and 1 == 0) {
            abs(index % words.size)
        } else {
            abs(words.size - index % words.size - 1)
        }
        return words[index]
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.game)

        //---------------------------------------
        // Create the man

        val dyingManView = findViewById<DyingManView>(R.id.dyingManView)

        //---------------------------------------
        // Create single-row grid for (initially invisible) guessed word and underscores

        val word = chooseWord()
        val wordFontSize = min(300f/word.length, 70f) // Both for underscores and guessed word

        val font = ResourcesCompat.getFont(applicationContext, R.font.comic)

        val grid_guessedWord = findViewById<GridLayout>(R.id.grid_guessedWord).apply {
            columnCount = word.length
            rowCount = 1
            alignmentMode = GridLayout.ALIGN_BOUNDS
        }
        val guessedLetterViews = ArrayList<TextView>()
        var numberOfCorrectlyGuessedLetters = 0

        for (index in word.indices) {
            val layoutParameters = GridLayout.LayoutParams().apply {
                columnSpec = GridLayout.spec(index)
                rowSpec = GridLayout.spec(0)
            }

            val textView_underscore = TextView(applicationContext).apply {
                text = "_"
                textSize = wordFontSize
                textAlignment = TextView.TEXT_ALIGNMENT_CENTER
                typeface = font
                width = wordFontSize.px
                height = (wordFontSize.px*1.5f).toInt()
                setTextColor(Color.BLACK)
            }
            grid_guessedWord.addView(textView_underscore, layoutParameters)

            val textView_letter = TextView(applicationContext).apply {
                text = word[index].toUpperCase().toString()
                textSize = wordFontSize
                textAlignment = TextView.TEXT_ALIGNMENT_CENTER
                typeface = font
                width = wordFontSize.px
                height = (wordFontSize.px*1.5f).toInt()
                visibility = TextView.INVISIBLE
                setTextColor(ContextCompat.getColor(applicationContext, R.color.colorPrimary))
            }
            grid_guessedWord.addView(textView_letter, layoutParameters)
            guessedLetterViews.add(textView_letter)
        }

        //---------------------------------------
        // Create alphabet grid

        val grid_letters = findViewById<GridLayout>(R.id.grid_letters).apply {
            columnCount = 6
            rowCount = 5
            alignmentMode = GridLayout.ALIGN_BOUNDS
        }
        for (letter in ALPHABET) {
            val textView_letter = TextView(applicationContext).apply {
                text = letter.toString()
                textSize = 40f
                textAlignment = TextView.TEXT_ALIGNMENT_CENTER
                typeface = font
                width = 50f.px
                height = 60f.px
                setTextColor(ContextCompat.getColor(applicationContext, R.color.colorPrimary))
            }
            textView_letter.isClickable = true
            textView_letter.setOnClickListener {
                var foundMatchingLetters = false
                for (guessedLetter in guessedLetterViews) {
                    if (guessedLetter.text == textView_letter.text) {
                        guessedLetter.visibility = TextView.VISIBLE
                        foundMatchingLetters = true
                        numberOfCorrectlyGuessedLetters++
                    }
                }
                textView_letter.visibility = TextView.INVISIBLE
                if (!foundMatchingLetters) {
                    dyingManView.deathProgress = min(1f, dyingManView.deathProgress + 1f/NUMBER_OF_FAILED_ATTEMPTS_BEFORE_DEATH)
                    runOnUiThread {
                        dyingManView.invalidate()
                    }
                    if (dyingManView.deathProgress == 1f) {
                        // Game over! Show the missing letters in black and start the game over screen after a delay
                        for (guessedLetter in guessedLetterViews) {
                            if (guessedLetter.visibility == TextView.INVISIBLE) {
                                guessedLetter.setTextColor(Color.BLACK)
                                guessedLetter.visibility = TextView.VISIBLE
                            }
                        }
                        Handler().postDelayed({
                            finish()
                            startActivity(Intent(this, GameOver::class.java).apply {
                                putExtra(MESSAGE_DIFFICULTY_MEAN, intent.getFloatExtra(MESSAGE_DIFFICULTY_MEAN, 0.5f))
                                putExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, intent.getFloatExtra(MESSAGE_DIFFICULTY_STANDARD_DEVIATION, 0.5f))
                            })
                            overridePendingTransition(0, 0)
                        }, 1000)
                    }
                }
                else if (numberOfCorrectlyGuessedLetters == word.length) {

                }
            }
            grid_letters.addView(textView_letter)
        }
    }
}
