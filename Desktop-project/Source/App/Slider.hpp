#pragma once
#include <AvoGUI.hpp>

class Slider : public AvoGUI::View
{
private:
	static constexpr TRACK_HEIGHT = 3.f;
	static constexpr KNOB_RADIUS = 10.f;

public:
	Slider(View* p_parent, float p_width) :
		View(p_parent)
	{
		setSize(p_width, KNOB_RADIUS * 2.f);
	}

	void draw(AvoGUI::DrawingContext* p_context) override
	{

	}
};
