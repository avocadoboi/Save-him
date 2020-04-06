package com.bjornsundin.save_him

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import com.google.android.material.button.MaterialButton

class StartScreen : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.start_screen)

        findViewById<MaterialButton>(R.id.button_play).setOnClickListener {
            startActivity(Intent(this, ChooseDifficulty::class.java))
            overridePendingTransition(0, 0)
        }
    }
}
