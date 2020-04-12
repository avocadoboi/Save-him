#pragma once

#include "../StartScreen/StartScreen.hpp"
#include "../../Resources/Colors.hpp"

#include <AvoGUI.hpp>
#include <stack>

//------------------------------

class App : public AvoGUI::Gui
{
public:
    App()
    {
        create("Save him", 500, 400);
        waitForFinish();
    }

    void createContent()
    {
        setThemeColor(AvoGUI::ThemeColors::primary, Colors::primary);
        setThemeColor(AvoGUI::ThemeColors::primaryOnBackground, Colors::primary);

        //------------------------------
        // Load font

        getDrawingContext()->addFont(Paths::font);

        AvoGUI::TextProperties textProperties;
        textProperties.fontFamilyName = "Comic Sans MS";
        getDrawingContext()->setDefaultTextProperties(textProperties);

        //------------------------------

        launchScreen(new StartScreen(this));
    }

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
    void goBack()
    {
        if (m_screenStack.size() > 1)
        {
            removeChild(m_screenStack.top());
            m_screenStack.pop();
            m_screenStack.top()->setIsVisible(true);
            invalidate();
        }
    }
    void returnToHome()
    {
        while (m_screenStack.size() > 1)
        {
            removeChild(m_screenStack.top());
            m_screenStack.pop();
        }
        m_screenStack.top()->setIsVisible(true);
        invalidate();
    }
    void handleSizeChange()
    {
        if (!m_screenStack.empty())
        {
            m_screenStack.top()->setSize(getSize());
        }
    }

};
