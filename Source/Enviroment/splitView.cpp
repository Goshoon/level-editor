#include "splitView.hpp"
// Libraries
#include <iostream>
// Own
#include "level.hpp"
#include "AssetManager.hpp"

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
	topRect.x = 0;
	topRect.y = 0;
	topRect.w = area.w;
	topRect.h = dividerY;

	// Bottom panel
	bottomRect.x = 0;
	bottomRect.y = dividerY + 5;
	bottomRect.w = area.w;
	bottomRect.h = area.h - dividerY - 5;

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