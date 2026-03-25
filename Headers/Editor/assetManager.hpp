#pragma once
#include <SDL3/SDL.h>
#include "panel.hpp"
class AssetManager : public Panel
{
public:
	AssetManager();
	void Update();
	void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};