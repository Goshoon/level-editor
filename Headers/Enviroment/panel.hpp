#pragma once
#include "math.hpp"

class Panel
{
public:
	virtual void Render(SDL_Renderer* renderer, const vec4<float>& area);
	SDL_FRect
};