#pragma once

#include "Button.hpp"
#include "../Resources/Paths.hpp"
#include "../Resources/Strings.hpp"

//------------------------------

class App;

class StartScreen : public AvoGUI::View
{
private:
	AvoGUI::Image m_backgroundImage = getGui()->getDrawingContext()->createImage(Paths::startScreenBackground);
	AvoGUI::Text m_title = getGui()->getDrawingContext()->createText(Strings::saveHim, 50.f);
	Button* m_playButton = new Button(this, Strings::play);

public:
	void handleSizeChange() override
	{
		m_backgroundImage.setSize(getSize());
		m_title.setCenter(getCenterX(), getHeight()*0.3f);
		m_playButton->setCenter(getCenterX(), getHeight()*0.7f);
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->drawImage(m_backgroundImage);

		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::primary));
		p_context->drawText(m_title);
	}

private:
	void startGame();

public:
	StartScreen(View* p_parent) :
		View{ p_parent }
	{
		m_backgroundImage.setBoundsSizing(AvoGUI::ImageBoundsSizing::Fill);
		m_backgroundImage.setOpacity(0.6f);

		enableMouseEvents();

		m_playButton->clickListeners += [this] { startGame(); };
	}
};
