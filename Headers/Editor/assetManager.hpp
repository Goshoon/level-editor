#pragma once
#include <SDL3/SDL.h>
#include "panel.hpp"
#include "mouseState.hpp"

class AssetManager : public Panel
{
public:
	AssetManager();
	void Update(MouseState& mouse, const SDL_FRect& area);
	void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};