#pragma once

#include "../App/Button.hpp"

#include <AvoGUI.hpp>

//------------------------------

class App;

class ChooseDifficulty : public AvoGUI::View
{
private:
	App* m_app;

	AvoGUI::Text* m_title{ getGui()->getDrawingContext()->createText(Strings::chooseDifficulty, 40.f) };

public:
	ChooseDifficulty(App* p_parent) :
		View(p_parent), m_app(p_parent)
	{
		enableMouseEvents();
	}
	~ChooseDifficulty()
	{
		m_title->forget();
	}

	void handleSizeChange() override
	{
		m_title->setCenter(getCenterX(), getHeight() * 0.3f);
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->drawText(m_title);
	}
};
