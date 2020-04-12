package com.bjornsundin.save_him

import android.content.Context
import android.graphics.Canvas
import android.util.AttributeSet
import android.view.View
import androidx.core.content.ContextCompat
import androidx.core.graphics.drawable.updateBounds
import kotlin.math.max

class DyingManView(p_context: Context, p_layoutAttributes: AttributeSet): View(p_context, p_layoutAttributes) {
    private val m_manImage = ContextCompat.getDrawable(p_context, R.drawable.man)
    private val m_rockImage = ContextCompat.getDrawable(p_context, R.drawable.rock)

    // Between 0 and 1
    var deathProgress = 0f

    override fun onDraw(p_canvas: Canvas) {
        if (m_rockImage == null) {
            return
        }

        val rockWidth = m_rockImage.intrinsicWidth/6
        val rockHeight = m_rockImage.intrinsicHeight/6
        val rockTop = (deathProgress*(height - rockHeight)).toInt()

        if (m_manImage != null) {
            val manWidth = m_manImage.intrinsicWidth/6
            val manHeight = m_manImage.intrinsicHeight/6
            m_manImage.updateBounds(
                (width - manWidth)/2,
                max(height - manHeight, rockTop + rockHeight),
                (width + manWidth)/2,
                height
            )
            m_manImage.draw(p_canvas)
        }

        m_rockImage.updateBounds((width - rockWidth)/2, rockTop, (width + rockWidth)/2, rockTop + rockHeight)
        m_rockImage.draw(p_canvas)
    }
}