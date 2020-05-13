#pragma once

#include "App.hpp"
#include "Button.hpp"

class GameOver : public AvoGUI::View
{
private:
	AvoGUI::TextView* m_gameOverText;
	AvoGUI::Image m_man;
public:
	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->drawImage(m_man);
		p_context->drawImage(m_man);
	}

	GameOver(View* p_parent, bool p_won) :
		View(p_parent)
	{
		auto context = getDrawingContext();
		if (p_won)
		{
			m_man = context->createImage(Paths::happyMan);
			//m_gameOverText = new AvoGUI::TextView(this, )
		}
		else
		{
			m_man = context->createImage(Paths::sadMan);
		}


	}
};
