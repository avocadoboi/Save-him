#pragma once

#include "StartScreen.hpp"
#include "../Resources/Colors.hpp"

#include <stack>

//------------------------------

class App : public AvoGUI::Gui
{
public:
	inline static AvoGUI::Point<float> const
		INITIAL_SIZE{ 500.f, 500.f },
		MIN_SIZE{ 440.f, 410.f },
		MAX_SIZE{ 700.f, 600.f };

private:
	std::stack<AvoGUI::View*> m_screenStack;

public:
	void launchScreen(AvoGUI::View* p_view)
	{
		if (!m_screenStack.empty())
		{
			m_screenStack.top()->setIsVisible(false);
		}
		m_screenStack.push(p_view);
		p_view->setSize(getSize());
		invalidate();
	}
	void closeScreen()
	{
		if (m_screenStack.size() > 1)
		{
			removeChildView(m_screenStack.top());
			m_screenStack.pop();
			m_screenStack.top()->setIsVisible(true);
			m_screenStack.top()->setSize(getSize());
			invalidate();
		}
	}
	void returnToHome()
	{
		while (m_screenStack.size() > 1)
		{
			removeChildView(m_screenStack.top());
			m_screenStack.pop();
		}
		m_screenStack.top()->setIsVisible(true);
		m_screenStack.top()->setSize(getSize());
		invalidate();
	}

	void handleSizeChange()
	{
		if (!m_screenStack.empty())
		{
			m_screenStack.top()->setSize(getSize());
		}
	}

	//------------------------------

	App()
	{
		create("Save him", INITIAL_SIZE);
		getWindow()->setMinSize(MIN_SIZE);
		getWindow()->setMaxSize(MAX_SIZE);

		setThemeColor(AvoGUI::ThemeColors::primary, Colors::primary);
		setThemeColor(AvoGUI::ThemeColors::primaryOnBackground, Colors::primary);
		setThemeColor(AvoGUI::ThemeColors::background, Colors::background);
		setThemeColor(AvoGUI::ThemeColors::onBackground, Colors::onBackground);

		//------------------------------
		// Load font

		getDrawingContext()->addFont(Paths::font);

		AvoGUI::TextProperties textProperties;
		textProperties.fontFamilyName = "Comic Sans MS";
		getDrawingContext()->setDefaultTextProperties(textProperties);

		//------------------------------

		launchScreen(new StartScreen{ this });

		run();
	}
};
