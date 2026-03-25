#include "splitView.hpp"

void SplitView::Update(MouseState& mouse, const SDL_FRect& area)
{
	// Drag windows!
	float divisionLine = area.h * ratio;
	short divisionBorder = 2;
	if (mouse.mouseButtonLeft)
	{
		if (mouse.f_mousePosition.y < divisionLine+divisionBorder && mouse.f_mousePosition.y > divisionLine-divisionBorder)
			dragging = true;

		if (dragging)
			ratio = mouse.f_mousePosition.y / area.h;
	}
	else
	{
		dragging = false;
	}
}

void SplitView::Render(SDL_Renderer* renderer, const SDL_FRect& area)
{
	// area.w = width
	// area.h = height
	float dividerY = (area.h * ratio);

	// Top panel
	SDL_FRect topRect = { 0, 0, area.w, dividerY };

	// Bottom panel
	SDL_FRect bottomRect = { 0, dividerY + 5, area.w, area.h - dividerY - 5 };

	// Draw panels
	if (top != nullptr)
	{
		top->Render(renderer, topRect);
	}
	else
	{
		std::cout << "Error: no top panel to display!\n";
	}

	if (bottom != nullptr)
	{
		bottom->Render(renderer, bottomRect);
	}
	else
	{
		std::cout << "Error: no bottom panel to display!\n";
	}
}