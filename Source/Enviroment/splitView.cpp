#include "splitView.hpp"
// Libraries
#include <iostream>
// Own
#include "level.hpp"
#include "AssetManager.hpp"

void SplitView::Update(KeyboardState& keyboard, MouseState& mouse, const SDL_FRect& area)
{
	// Drag windows!
	float divisionLine = area.h * ratio;
	short divisionBorder = 5;
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

	tabCooldown --;
	if (keyboard.tab && tabCooldown <= 0)
	{
		tabCooldown = 600;
		switch(viewMode)
		{
			default:
			{
				ratio = 0.5f;
				viewMode = TOP_VIEW;
			}
			break;
			case TOP_VIEW:
			{
				viewMode = BOTTOM_VIEW;
			}
			break;
			case BOTTOM_VIEW:
			{
				viewMode = DEFAULT;
			}
			break;
		}
	}
}

void SplitView::Render(SDL_Renderer* renderer, const SDL_FRect& area)
{
	// area.w = width
	// area.h = height
	switch (viewMode)
	{
		default:
		case DEFAULT:
		{
			float dividerY = (area.h * ratio);

			// Top panel
			topRect.x = 0;
			topRect.y = verticalPadding;
			topRect.w = area.w;
			topRect.h = dividerY;

			// Bottom panel
			bottomRect.x = 0;
			bottomRect.y = dividerY + 5;
			bottomRect.w = area.w;
			bottomRect.h = area.h - dividerY - 5;
		}
		break;
		case TOP_VIEW:
		{
			// Top panel
			topRect.x = 0;
			topRect.y = verticalPadding;
			topRect.w = area.w;
			topRect.h = area.h;

			// Bottom panel
			bottomRect.x = 0;
			bottomRect.y = 0;
			bottomRect.w = 0;
			bottomRect.h = 0;
		}
		break;
		case BOTTOM_VIEW:
		{
			// Top panel
			topRect.x = 0;
			topRect.y = 0;
			topRect.w = 0;
			topRect.h = 0;

			// Bottom panel
			bottomRect.x = 0;
			bottomRect.y = verticalPadding;
			bottomRect.w = area.w;
			bottomRect.h = area.h;
		}
		break;
	}

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

