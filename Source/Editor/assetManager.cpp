#include "assetManager.hpp"
#include <SDL3/SDL.h>

AssetManager::AssetManager() {}

void AssetManager::Update(MouseState& mouse, const SDL_FRect& area) 
{

}

void AssetManager::Render(SDL_Renderer* renderer, const SDL_FRect& area) 
{
	// Panel background
    SDL_SetRenderDrawColor(renderer, 52, 58, 64, 255);
    SDL_RenderFillRect(renderer, &area);
}