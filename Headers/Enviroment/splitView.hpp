#pragma once
#include <iostream>
#include <memory>
#include <SDL3/SDL.h>

#include "mouseState.hpp"
#include "panel.hpp"
#include "math.hpp"

class SplitView
{
public:
	float ratio = 0.5f;
	bool dragging = false;

	std::shared_ptr<Panel> top = nullptr;
    std::shared_ptr<Panel> bottom = nullptr;

    void Update(MouseState& mouse, const SDL_FRect& area);
    void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};