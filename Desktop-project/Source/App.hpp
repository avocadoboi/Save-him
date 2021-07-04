#pragma once

#include "StartScreen.hpp"
#include "../Resources/colors.hpp"

#include <stack>

//------------------------------

namespace hangman_desktop {

/*
	concept HasGuiCallbacks evaluates to true
*/
class GuiManager {
private:
	using Styles = avo::WindowStyleFlags;

	avo::Gui<GuiManager> _gui = avo::make_gui()
		.with_manager(this)
		.with_title("Save him")
		.with_window_styles(Styles::MinimizeButton | Styles::CloseButton | Styles::Resizable)
		.with_initial_size({500.f, 500.f})
		.with_size_range({440.f, 410.f}, {700.f, 600.f})
		.with_theme_colors({
			{avo::theme_colors::primary, colors::primary},
			{avo::theme_colors::background, colors::background},
			{avo::theme_colors::onBackground, colors::onBackground}
		})
		.finish();

	friend class avo::Gui<GuiManager>;
	auto handle_size_change(Gui<GuiManager>&) -> void {
		if (!_screen_stack.empty()) {
			_screen_stack.top()->size(_gui.size());
		}
	}

	std::stack<avo::View*> _screen_stack;

public:
	auto launch_screen(avo::View* const view) -> void {
		if (!_screen_stack.empty()) {
			_screen_stack.top()->is_visible(false);
		}
		_screen_stack.push(view);
		view->size(_gui.size());
		invalidate();
	}
	auto close_screen() -> void {
		if (_screen_stack.size() > 1) {
			_gui.remove_view(_screen_stack.top());
			_screen_stack.pop();
			_screen_stack.top()->is_visible(true);
			_screen_stack.top()->size(_gui.size());
		}
	}
	auto return_to_home() -> void {
		while (_screen_stack.size() > 1) {
			_gui.remove_view(_screen_stack.top());
			_screen_stack.pop();
		}
		_screen_stack.top()->is_visible(true);
		_screen_stack.top()->size(_gui.size());
	}

	//------------------------------

	GuiManager() {
		_gui.graphics()->add_font(paths::font);
		_gui.graphics()->default_text_properties({ .font_family = "Comic Sans MS" });

		launch_screen(_gui.add_view<StartScreen>());

		_gui.run();
	}
};

} // namespace hangman_desktop
