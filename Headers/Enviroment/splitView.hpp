#pragma once
#include "panel.hpp"

class SplitView
{
public:
	float ratio = 0.7f;
	bool dragging = false;

	Panel* top;
    Panel* bottom;

    void Render(const vec2<float>& area);
};