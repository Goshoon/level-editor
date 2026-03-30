#pragma once
#include "math.hpp"

struct SDL_Renderer;
struct SDL_FRect;

class Panel
{
public:
	virtual void Render(SDL_Renderer* renderer, const SDL_FRect& area) = 0;
};