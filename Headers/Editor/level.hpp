#pragma once
#include <SDL3/SDL.h>

#include <memory>
#include <vector>
#include <cstdint>

#include "math.hpp"
#include "panel.hpp"


class Level : public Panel
{
public:
	Level();
	Level(int w, int h);

	float width;
	float height;
	float scale;

	vec2<float> f_cursorPosition;
	vec4<float> f_cameraPosition;
	vec4<int> rgba_backgroundColor;

	void Update();
	void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};