#include "topbar.hpp"
// External libraries
#include <SDL3/SDL.h>
// Own
#include "math.hpp"
#include "mouseState.hpp"
#include "collision.hpp"

// HEX: 34618a
// RGB: 52, 97, 138
Topbar::Topbar()
{
	// Sprite
	displayButton.src.x = 0;
	displayButton.src.y = 0;
	displayButton.src.z = 256;
	displayButton.src.w = 256;

	// Destination
	displayButton.dst.x = 0;
	displayButton.dst.y = 28;
	displayButton.dst.z = 32;
	displayButton.dst.w = 32;
}

void Topbar::Update()
{
	// std::cout << "POINTING: " << resolution << " AMMOUNT: " << resolution->w << " : " << displayButton.dst.x << std::endl;
	const float cursorSize = 8.0f;
	if (!showContent)
	{
		displayButton.dst.x = Lerp(displayButton.dst.x, 0.0f, 0.05f);

		SDL_FRect tmpMouse = { mouse->f_mousePosition.x, mouse->f_mousePosition.y, cursorSize, cursorSize };
		SDL_FRect tmpDisplay = { displayButton.dst.x, displayButton.dst.y, displayButton.dst.z, displayButton.dst.w };
		bool onArea = Collide( tmpDisplay, tmpMouse );

		if (mouse->mouseButtonLeft && onArea)
			showContent = true;
	}
	else
	{
		displayButton.dst.x = Lerp(displayButton.dst.x, resolution->w-64, 0.02f);
		//displayButton.dst.y = 28;

		SDL_FRect tmpMouse = { mouse->f_mousePosition.x, mouse->f_mousePosition.y, cursorSize, cursorSize };
		SDL_FRect tmpDisplay = { displayButton.dst.x, displayButton.dst.y, displayButton.dst.z, displayButton.dst.w };
		bool onArea = Collide( tmpDisplay , tmpMouse );

		if (mouse->mouseButtonLeft && onArea)
			showContent = false;
		
	}
}

void Topbar::Render(SDL_Renderer* renderer)
{
	// Draw navigation area
	SDL_SetRenderDrawColor(renderer, 52, 97, 138, 255);
	SDL_FRect navigationArea = { 0, 28, displayButton.dst.x, 32 };
	SDL_RenderFillRect(renderer, &navigationArea);

	// Draw navigation button
	SDL_FRect src = { displayButton.src.x, displayButton.src.y, displayButton.src.z, displayButton.src.w };
	SDL_FRect dst = { displayButton.dst.x, displayButton.dst.y, displayButton.dst.z, displayButton.dst.w };
	SDL_RenderTexture(renderer, displayButton.image, &src, &dst);

}