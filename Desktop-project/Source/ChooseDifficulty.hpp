#pragma once

#include "App.hpp"
#include "Game.hpp"

#include "Slider.hpp"
#include "../Resources/Strings.hpp"
#include "../Resources/Paths.hpp"

//------------------------------

class App;

class ChooseDifficulty : public AvoGUI::View
{
public:
	static constexpr float TITLE_POSITION = 0.2f;
	static constexpr float MEAN_POSITION = 0.4f;
	static constexpr float STANDARD_DEVIATION_POSITION = 0.6f;
	static constexpr float BUTTON_POSITION = 0.8f;
	static constexpr float BUTTON_SCALE = 0.7f;

	static constexpr float MAN_WIDTH = 80.f;
	static constexpr float SLIDER_WIDTH = 200.f;
	static constexpr float MARGIN_BETWEEN_TEXT_AND_SLIDER = 15.f;

	//------------------------------

private:
	AvoGUI::Text m_title = getDrawingContext()->createText(Strings::chooseDifficulty, 40.f);

	AvoGUI::Image m_man = getDrawingContext()->createImage(Paths::man);

	AvoGUI::Text m_text_mean = getDrawingContext()->createText(Strings::mean, 25.f);
	Slider* m_slider_mean = new Slider{ this, SLIDER_WIDTH };

	AvoGUI::Text m_text_standardDeviation = getDrawingContext()->createText(Strings::standardDeviation, 25.f);
	Slider* m_slider_standardDeviation = new Slider{ this, SLIDER_WIDTH };

	Button* m_button_play = new Button{ this, Strings::saveTheMan };

public:
	void handleSizeChange() override
	{
		m_title.setCenter(getCenterX(), getHeight() * TITLE_POSITION);

		m_man.setCenter(getWidth() * 0.25f, getHeight()*0.5f);

		float rightCenter = getWidth()*0.6f;
		m_slider_mean->setCenterX(rightCenter);
		m_slider_mean->setTop(getHeight() * MEAN_POSITION);
		m_text_mean.setCenterX(rightCenter);
		m_text_mean.setBottom(m_slider_mean->getTop() - MARGIN_BETWEEN_TEXT_AND_SLIDER);

		m_slider_standardDeviation->setCenterX(rightCenter);
		m_slider_standardDeviation->setTop(getHeight() * STANDARD_DEVIATION_POSITION);
		m_text_standardDeviation.setCenterX(rightCenter);
		m_text_standardDeviation.setBottom(m_slider_standardDeviation->getTop() - MARGIN_BETWEEN_TEXT_AND_SLIDER);

		m_button_play->setCenter(getCenterX(), getHeight() * BUTTON_POSITION);
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(getThemeColor(AvoGUI::ThemeColors::onBackground));
		p_context->drawImage(m_man);
		p_context->drawText(m_title);
		p_context->drawText(m_text_mean);
		p_context->drawText(m_text_standardDeviation);
	}

	ChooseDifficulty(View* p_parent) :
		View{ p_parent }
	{
		enableMouseEvents();

		m_man.setBoundsSizing(AvoGUI::ImageBoundsSizing::Contain);
		m_man.setWidth(MAN_WIDTH);

		m_button_play->setThemeValue(ThemeValues::buttonScale, BUTTON_SCALE);
		m_button_play->clickListeners += [this] {
			auto app = getParent<App>();
			app->launchScreen(new Game{ app, m_slider_mean->getValue(), m_slider_standardDeviation->getValue() });
		};
	}
};
