#include "level.hpp"
#include <SDL3/SDL.h>

Level::Level() {}

Level::Level(int w, int h)
{
	levelPosition.x = 0;
	levelPosition.y = 0;
	levelPosition.z = w;
	levelPosition.w = h;
	rgba_backgroundColor.x = 255;
	rgba_backgroundColor.y = 255;
	rgba_backgroundColor.z = 255;
	rgba_backgroundColor.w = 255;
}

void Level::Update(MouseState& mouse, const SDL_FRect& area)
{
	if (dragging)
	{
    	float dx = (mouse.f_mousePosition.x - f_oldMousePosition.x) / scale;
    	float dy = (mouse.f_mousePosition.y - f_oldMousePosition.y) / scale;

    	f_cameraPosition.x -= dx;
    	f_cameraPosition.y -= dy;

    	f_oldMousePosition = mouse.f_mousePosition;
	}

	if (mouse.f_mousePosition.y < area.h && mouse.f_mousePosition.y > area.y) // on level panel bounds
	{
		if (mouse.mouseButtonRight) // Mouse Wheel button later
		{
			dragging = true;
			f_oldMousePosition.x = mouse.f_mousePosition.x;
			f_oldMousePosition.y = mouse.f_mousePosition.y;
		}
	}

	if (!mouse.mouseButtonRight) // Mouse Wheel button later
		dragging = false;

	if (mouse.mouseWheelUp)
		scale+=0.05;

	if (mouse.mouseWheelDown)
		scale-=0.05;

	scale = std::clamp(scale, 0.8f, 5.0f);
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

    // Draw level background
    SDL_SetRenderDrawColor(renderer,
        rgba_backgroundColor.x,
        rgba_backgroundColor.y,
        rgba_backgroundColor.z,
        rgba_backgroundColor.w
    );
    SDL_RenderFillRect(renderer, &levelRect);

    // Grid Render
    if (grid)
    {
    	SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255); // grid color
	
    	// Determine visible world bounds
    	float worldLeft   = f_cameraPosition.x;
    	float worldTop    = f_cameraPosition.y;
    	float worldRight  = f_cameraPosition.x + (area.w / scale);
    	float worldBottom = f_cameraPosition.y + (area.h / scale);
	
    	// Snap start positions to grid
    	float startX = std::floor(worldLeft / gridSizeX) * gridSizeX;
    	float startY = std::floor(worldTop  / gridSizeY) * gridSizeY;
	
    	// Vertical lines
    	for (float x = startX; x < worldRight; x += gridSizeX)
    	{
    	    float screenX = area.x + (x - f_cameraPosition.x) * scale;
	
    	    SDL_RenderLine(renderer,
    	        (int)screenX, (int)area.y,
    	        (int)screenX, (int)(area.y + area.h)
    	    );
    	}
	
    	// Horizontal lines
    	for (float y = startY; y < worldBottom; y += gridSizeY)
    	{
    	    float screenY = area.y + (y - f_cameraPosition.y) * scale;
	
    	    SDL_RenderLine(renderer,
    	        (int)area.x, (int)screenY,
    	        (int)(area.x + area.w), (int)screenY
    	    );
    	}
	}

    // Disable clipping
    SDL_SetRenderClipRect(renderer, nullptr);
}