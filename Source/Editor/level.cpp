#include "level.hpp"

Level::Level() {}

Level::Level(int w, int h)
{
	levelPosition.x = 0;
	levelPosition.y = 0;
	levelPosition.z = w;
	levelPosition.w = h;
	rgba_backgroundColor.x = 100;
	rgba_backgroundColor.y = 0;
	rgba_backgroundColor.z = 0;
	rgba_backgroundColor.w = 255;
}

void Level::Update(MouseState& mouse, const SDL_FRect& area)
{
	if (dragging)
	{
    	float dx = mouse.f_mousePosition.x - f_oldMousePosition.x;
    	float dy = mouse.f_mousePosition.y - f_oldMousePosition.y;

    	f_cameraPosition.x -= dx;
    	f_cameraPosition.y -= dy;

    	f_oldMousePosition = mouse.f_mousePosition;
	}
	else
	{
		if (mouse.f_mousePosition.y < area.y && mouse.f_mousePosition.y > 0) // on level panel bounds
		{
			if (mouse.mouseButtonRight) // Mouse Wheel button later
			{
				dragging = true;
				f_oldMousePosition.x = mouse.f_mousePosition.x;
				f_oldMousePosition.y = mouse.f_mousePosition.y;
			}
		}
	}

	if (!mouse.mouseButtonRight) // Mouse Wheel button later
		dragging = false;
}

void Level::Render(SDL_Renderer* renderer, const SDL_FRect& area)
{
    // Panel background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &area);

    // Enable clipping to panel
    SDL_Rect clipRect;
	clipRect.x = (int)area.x;
	clipRect.y = (int)area.y;
	clipRect.w = (int)area.w;
	clipRect.h = (int)area.h;

	SDL_SetRenderClipRect(renderer, &clipRect);
	
    // Level rect (world → screen)
    SDL_FRect levelRect;
    levelRect.x = area.x + (levelPosition.x - f_cameraPosition.x) * scale;
    levelRect.y = area.y + (levelPosition.y - f_cameraPosition.y) * scale;
    levelRect.w = levelPosition.z * scale;
    levelRect.h = levelPosition.w * scale;

    // Draw level
    SDL_SetRenderDrawColor(renderer,
        rgba_backgroundColor.x,
        rgba_backgroundColor.y,
        rgba_backgroundColor.z,
        rgba_backgroundColor.w
    );
    SDL_RenderFillRect(renderer, &levelRect);

    // Disable clipping
    SDL_SetRenderClipRect(renderer, nullptr);
}