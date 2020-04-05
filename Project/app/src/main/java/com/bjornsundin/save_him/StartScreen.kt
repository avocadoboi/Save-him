package com.bjornsundin.save_him

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class StartScreen : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.start_screen)
    }

    fun play(p_view: View) {
        startActivity(Intent(this, ChooseDifficulty::class.java))
    }
}
