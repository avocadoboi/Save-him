#pragma once
#include <AvoGUI.hpp>

class Button : public AvoGUI::View
{
private:
	static constexpr float DEFAULT_SIZE = 40.f;
	static constexpr float STROKE_WIDTH = 5.f;
	
	AvoGUI::Text* m_text{ nullptr };

public:
	Button(AvoGUI::View* p_parent, std::string const& p_string) :
		View(p_parent)
	{
		m_text = getGui()->getDrawingContext()->createText(p_string, DEFAULT_SIZE);
		
		setCornerRadius(DEFAULT_SIZE * 0.5f);
		setCursor(AvoGUI::Cursor::Hand);

		new AvoGUI::Ripple(this, AvoGUI::Color(getThemeColor(AvoGUI::ThemeColors::primary), 0.3f));

		updateLayout();
	}
	~Button()
	{
		m_text->forget();
	}

	void updateLayout()
	{
		setCornerRadius(m_text->getHeight() * 0.4f);
		setSize(m_text->getWidth() + m_text->getHeight() * 1.5f, m_text->getHeight() * 2.f);
	}
	void handleSizeChange() override
	{
		m_text->setCenter(getCenter());
	}
	void setScale(float p_factor)
	{
		m_text->setFontSize(DEFAULT_SIZE * p_factor);
		m_text->fitSizeToText();
		updateLayout();
		handleSizeChange();
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(AvoGUI::Color(getThemeColor(AvoGUI::ThemeColors::background), 0.8f));
		p_context->fillRectangle(getSize());

		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary));
		p_context->drawText(m_text);

		p_context->strokeRectangle(getSize(), getCorners(), STROKE_WIDTH);
	}
	void drawOverlay(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary));
		p_context->strokeRectangle(getSize(), getCorners(), STROKE_WIDTH);
	}
};
