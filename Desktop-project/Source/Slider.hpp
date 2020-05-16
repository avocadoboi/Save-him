#pragma once

#include <AvoGUI.hpp>

class Slider : public AvoGUI::View
{
private:
	static constexpr float TRACK_HEIGHT = 4.f;
	static constexpr float KNOB_RADIUS = 10.f;

private:
	bool m_isDragging = false;
public:
	void handleMouseDown(AvoGUI::MouseEvent const& p_event) override
	{
		m_isDragging = true;
	}
	void handleMouseUp(AvoGUI::MouseEvent const& p_event) override
	{
		m_isDragging = false;
		handleMouseMove(p_event);
	}

private:
	bool m_isHoveringKnob = false;
	float m_knobScale = 0.7f;
	AvoGUI::Animation* m_hoverAnimation = createAnimation(AvoGUI::ThemeEasings::out, 300, [=](float p_value) {
		m_knobScale = 0.7f + 0.3f * p_value;
		invalidate();
	});

	bool getIsPointOverKnob(float p_x, float p_y)
	{
		return getSize().getIsContaining(p_x, p_y) 
			&& AvoGUI::Point<float>::getDistanceSquared(p_x, p_y, m_knobPosition, getHeight() * 0.5f) < KNOB_RADIUS * KNOB_RADIUS;
	}
public:
	void handleMouseMove(AvoGUI::MouseEvent const& p_event) override
	{
		bool isHovering = getIsPointOverKnob(p_event.x, p_event.y) || m_isDragging;
		if (isHovering && !m_isHoveringKnob)
		{
			m_hoverAnimation->play(false);
		}
		else if (!isHovering && m_isHoveringKnob)
		{
			m_hoverAnimation->play(true);
		}
		m_isHoveringKnob = isHovering;
		if (m_isDragging)
		{
			setKnobPosition(p_event.x);
		}
	}
	void handleMouseLeave(AvoGUI::MouseEvent const& p_event) override
	{
		handleMouseMove(p_event);
	}

	//------------------------------

private:
	float m_value;
	float m_knobPosition;
public:
	void setValue(float p_value)
	{
		p_value = AvoGUI::constrain(p_value);
		m_knobPosition = KNOB_RADIUS + p_value * (getWidth() - KNOB_RADIUS * 2);
		m_value = p_value;
		invalidate();
	}
	float getValue()
	{
		return m_value;
	}
	void setKnobPosition(float p_position)
	{
		setValue((p_position - KNOB_RADIUS) / (getWidth() - KNOB_RADIUS * 2));
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(AvoGUI::Color(getThemeColor(AvoGUI::ThemeColors::primary), 0.3f));
		p_context->fillRoundedRectangle(KNOB_RADIUS, (getHeight() - TRACK_HEIGHT)*0.5f, getWidth() - KNOB_RADIUS, (getHeight() + TRACK_HEIGHT) * 0.5f, TRACK_HEIGHT*0.5f);
	
		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary).setBrightness(0.8f));
		p_context->fillRoundedRectangle(KNOB_RADIUS, (getHeight() - TRACK_HEIGHT) * 0.5f, m_knobPosition, (getHeight() + TRACK_HEIGHT) * 0.5f, TRACK_HEIGHT * 0.5f);

		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary));
		p_context->fillCircle(m_knobPosition, getHeight() * 0.5f, KNOB_RADIUS*m_knobScale);
	}

	//------------------------------

	Slider(AvoGUI::View* p_parent, float p_width, float p_initialValue = 0.5f) :
		View{ p_parent }
	{
		setSize(p_width, KNOB_RADIUS * 2.f + 1.f);
		setValue(p_initialValue);
		enableMouseEvents();
	}
};
