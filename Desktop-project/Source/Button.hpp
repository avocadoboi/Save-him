#pragma once

#include <AvoGUI.hpp>

namespace ThemeValues
{
	inline AvoGUI::Id const buttonScale;
}
namespace ThemeColors
{
	inline AvoGUI::Id const buttonColor;
}

class Button : public AvoGUI::View
{
public:
	static constexpr float DEFAULT_SIZE = 40.f;
	static constexpr float STROKE_WIDTH = 5.f;
	
	//------------------------------

	AvoGUI::EventListeners<void()> clickListeners;

	void handleMouseUp(AvoGUI::MouseEvent const& p_event) override
	{
		if (getSize().getIsContaining(p_event.x, p_event.y) && p_event.mouseButton == AvoGUI::MouseButton::Left)
		{
			clickListeners();
		}
	}

	//------------------------------

private:
	void setScale(float p_factor)
	{
		m_text.setFontSize(DEFAULT_SIZE * p_factor);
		m_text.fitSizeToText();
		updateLayout();
		handleSizeChange();
	}
protected:
	void handleThemeValueChange(AvoGUI::Id const& p_id, float p_value) override
	{
		if (p_id == ThemeValues::buttonScale)
		{
			setScale(p_value);
		}
	}

private:
	AvoGUI::Text m_text;
public:
	void updateLayout()
	{
		setCornerRadius(m_text.getHeight() * 0.4f);
		setSize(m_text.getWidth() + m_text.getHeight() * 1.6f, m_text.getHeight() * 2.3f);
	}
	void handleSizeChange() override
	{
		m_text.setCenter(getCenter());
	}

	//------------------------------

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(AvoGUI::Color(getThemeColor(AvoGUI::ThemeColors::background), 0.8f));
		p_context->fillRectangle(getSize());

		p_context->setColor(getThemeColor(ThemeColors::buttonColor));
		p_context->drawText(m_text);
	}
	void drawOverlay(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(getThemeColor(ThemeColors::buttonColor));
		p_context->strokeRectangle(getSize(), getCorners(), STROKE_WIDTH);
	}

	//------------------------------

private:
	AvoGUI::Ripple* m_ripple = nullptr;
protected:
	void handleThemeColorChange(AvoGUI::Id const& p_id, AvoGUI::Color const& p_color) override
	{
		if (p_id == ThemeColors::buttonColor)
		{
			m_ripple->setColor(AvoGUI::Color(p_color, 0.3f));
		}
	}

	//------------------------------

public:
	Button(AvoGUI::View* p_parent, std::string const& p_string) :
		View{ p_parent },
		m_text{ getGui()->getDrawingContext()->createText(p_string, 0) }
	{
		initializeThemeValue(ThemeValues::buttonScale, 1.f);
		initializeThemeColor(ThemeColors::buttonColor, getThemeColor(AvoGUI::ThemeColors::primary));

		setScale(getThemeValue(ThemeValues::buttonScale));

		setCursor(AvoGUI::Cursor::Hand);

		m_ripple = new AvoGUI::Ripple{ this, AvoGUI::Color(getThemeColor(ThemeColors::buttonColor), 0.3f) };

		updateLayout();
	}
};
