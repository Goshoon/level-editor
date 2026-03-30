#pragma once
// SDL3
struct SDL_Frect;
struct SDL_Renderer;
// Own
#include "panel.hpp"
#include "mouseState.hpp"

class AssetManager : public Panel
{
public:
	AssetManager();
	void Update(MouseState& mouse, const SDL_FRect& area);
	void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};