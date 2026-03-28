#pragma once
#include <iostream>
#include <memory>
#include <SDL3/SDL.h>

#include "mouseState.hpp"
#include "panel.hpp"
#include "level.hpp"
#include "AssetManager.hpp"
#include "math.hpp"

class SplitView
{
public:
	float ratio = 0.5f;
	bool dragging = false;

	Level* top = nullptr;
    AssetManager* bottom = nullptr;
    SDL_FRect topRect;
	SDL_FRect bottomRect;

    void Update(MouseState& mouse, const SDL_FRect& area);
    void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};