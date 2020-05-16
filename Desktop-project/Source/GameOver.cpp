#include "GameOver.hpp"
#include "Game.hpp"

GameOver::GameOver(View* p_parent, bool p_won, float p_meanDifficulty, float p_standardDeviationDifficulty) :
	View{ p_parent }
{
	enableMouseEvents();

	setThemeValue(ThemeValues::buttonScale, 0.5f);

	auto context = getDrawingContext();
	m_gameOverText = new AvoGUI::TextView{ this, 40.f };
	if (p_won)
	{
		m_man = context->createImage(Paths::happyMan);
		m_gameOverText->setString(Strings::youWon);
		m_gameOverText->setColor(Colors::green);
		setThemeColor(ThemeColors::buttonColor, Colors::green);
	}
	else
	{
		m_man = context->createImage(Paths::sadMan);
		m_gameOverText->setString(Strings::youLost);
		m_gameOverText->setColor(Colors::red);
		setThemeColor(ThemeColors::buttonColor, Colors::red);
	}
	m_man.setSize(m_man.getSize() / 4.f);

	m_gameOverText->getText().setTextAlign(AvoGUI::TextAlign::Center);
	m_gameOverText->getText().setWordWrapping(AvoGUI::WordWrapping::WholeWord);

	auto app = (App*)p_parent;

	// Play again
	m_buttons[0]->clickListeners += [=] {
		app->closeScreen();
		app->launchScreen(new Game{ app, p_meanDifficulty, p_standardDeviationDifficulty });
	};

	// Change difficulty
	m_buttons[1]->clickListeners += [=] {
		app->closeScreen();
	};

	// Home
	m_buttons[2]->clickListeners += [=] {
		app->returnToHome();
	};
}