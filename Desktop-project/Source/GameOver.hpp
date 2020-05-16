#pragma once

#include "App.hpp"
#include "Button.hpp"

#include <array>

class GameOver : public AvoGUI::View
{
private:
	AvoGUI::TextView* m_gameOverText = nullptr;
	AvoGUI::Image m_man;

	std::array<Button*, 3> m_buttons = { 
		new Button(this, Strings::playAgain),
		new Button(this, Strings::changeDifficulty),
		new Button(this, Strings::home)
	};

public:
	void draw(AvoGUI::DrawingContext* p_context) override
	{
		m_man.setCenterX(getWidth() * 0.2f);
		p_context->drawImage(m_man);

		m_man.setCenterX(getWidth() * 0.8f);
		p_context->drawImage(m_man);
	}

	void handleSizeChange()
	{
		m_gameOverText->setWidth(getWidth() * 0.6f);
		m_gameOverText->fitHeightToText();
		m_gameOverText->setCenter(getCenterX(), getHeight() * 0.5f - 100.f);

		m_man.setCenterY(getHeight() * 0.5f);

		float top = m_gameOverText->getBottom() + 50.f;
		for (auto button : m_buttons)
		{
			button->setCenterX(getCenterX());
			button->setTop(top + 10.f);
			top = button->getBottom();
		}
	}

	GameOver(View* p_parent, bool p_won, float p_meanDifficulty, float p_standardDeviationDifficulty);
};
