#include "StartScreen.hpp"
#include "App.hpp"
#include "ChooseDifficulty.hpp"

void StartScreen::startGame()
{
	auto app = getParent<App>();
	app->launchScreen(new ChooseDifficulty(app));
}
