#include "StartScreen.hpp"
#include "../App/App.hpp"
#include "../ChooseDifficulty/ChooseDifficulty.hpp"

void StartScreen::startGame()
{
	m_app->launchScreen(new ChooseDifficulty(m_app));
}
