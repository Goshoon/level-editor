#include "level.hpp"

Level::Level() {}

Level::Level(int w, int h)
{
	width = w;
	height = h;
}

void Level::Update() {}

void Level::Render(SDL_Renderer* renderer, const SDL_FRect& area)
{
	// Render level background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_RenderFillRect(renderer, &area); 				// Panel background

	//SDL_SetRenderDrawColor(renderer, rgba_backgroundColor.x, rgba_backgroundColor.y, rgba_backgroundColor.z, rgba_backgroundColor.w );
	//SDL_RenderFillRect(renderer, &area); 				// Level area
}