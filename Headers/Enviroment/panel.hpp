#pragma once
#include <SDL3/SDL.h>
#include "math.hpp"

class Panel
{
public:
	virtual void Render(SDL_Renderer* renderer, const SDL_FRect& area) = 0;
};