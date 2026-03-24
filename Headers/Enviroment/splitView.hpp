#pragma once
#include <memory>
#include "panel.hpp"

class SplitView
{
public:
	float ratio = 0.7f;
	bool dragging = false;

	std::unique_ptr<Panel> top;
    std::unique_ptr<Panel> bottom;

    void Render(const vec4<float>& area);
};