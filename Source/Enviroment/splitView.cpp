#include "splitView.hpp"

void SplitView::Render(const vec4<float>& area)
{
	// area.x = width
	// area.y = height
	int dividerY = (int)(area.y * ratio);

	// Top panel
	vec4<float> topRect = { 0, 0, area.x, dividerY };

	// Bottom panel
	vec4<float> bottomRect = { 0, dividerY + 5, area.x, area.y - dividerY - 5 };

	// Draw panels
	top->Render(topRect);
	bottom->Render(bottomRect);
}