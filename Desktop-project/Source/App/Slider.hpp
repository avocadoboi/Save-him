#pragma once
#include <AvoGUI.hpp>

class Slider : public AvoGUI::View
{
private:
	static constexpr float TRACK_HEIGHT = 4.f;
	static constexpr float KNOB_RADIUS = 10.f;

	float m_value;

public:
	Slider(AvoGUI::View* p_parent, float p_width, float p_initialValue = 0.5f) :
		View(p_parent), m_value(p_initialValue)
	{
		setSize(p_width, KNOB_RADIUS * 2.f);
		enableMouseEvents();
	}

	void setValue(float p_value)
	{
		m_value = p_value;
		invalidate();
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(AvoGUI::Color(getThemeColor(AvoGUI::ThemeColors::primary), 0.3f));
		p_context->fillRoundedRectangle(0.f, (getHeight() - TRACK_HEIGHT)*0.5f, getWidth(), (getHeight() + TRACK_HEIGHT) * 0.5f, TRACK_HEIGHT*0.5f);
	
		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary).setBrightness(0.8f));
		p_context->fillRoundedRectangle(0.f, (getHeight() - TRACK_HEIGHT) * 0.5f, getWidth() * m_value, (getHeight() + TRACK_HEIGHT) * 0.5f, TRACK_HEIGHT * 0.5f);

		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary));
		p_context->fillCircle(getWidth() * m_value, getHeight() * 0.5f, KNOB_RADIUS);
	}
};
