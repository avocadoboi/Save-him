#include "App.hpp"

// Remove console window for release
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

auto main() -> int {
	auto app = hangman_slutprojekt::App{};
}
