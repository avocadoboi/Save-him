#pragma once

#include "../App/Button.hpp"
#include "../../Resources/Paths.hpp"
#include "../../Resources/Strings.hpp"

#include <AvoGUI.hpp>

//------------------------------

class App;

class StartScreen : public AvoGUI::View
{
private:
	App* m_app;

	AvoGUI::Image* m_backgroundImage{ getGui()->getDrawingContext()->createImage(Paths::startScreenBackground) };
	AvoGUI::Text* m_title{ getGui()->getDrawingContext()->createText(Strings::saveHim, 50.f) };
	Button* m_playButton{ new Button(this, Strings::play) };

public:
	StartScreen(View* p_parent) :
		View(p_parent), m_app((App*)p_parent)
	{
		m_backgroundImage->setBoundsSizing(AvoGUI::ImageBoundsSizing::Fill);

		enableMouseEvents();

		m_playButton->addMouseUpListener([this](AvoGUI::MouseEvent const) {
			startGame();
		});
	}
	~StartScreen()
	{
		m_backgroundImage->forget();
	}

	void startGame();
	void handleSizeChange() override
	{
		m_backgroundImage->setSize(getSize());
		m_title->setCenter(getCenterX(), getHeight()*0.3f);
		m_playButton->setCenter(getCenterX(), getHeight()*0.7f);
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->drawImage(m_backgroundImage);

		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary));
		p_context->drawText(m_title);
	}
};
