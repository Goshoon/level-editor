#include "level.hpp"

Level::Level() {}

Level::Level(int w, int h)
{
	width = w;
	height = h;
}

void Level::Update() {}

void Level::Render() 
{
	// Render level background
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );

	/*
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
    SDL_FRect squareRect = { 0, 0, width, height };
    SDL_RenderFillRect(renderer, &squareRect);
    */
}