#pragma once
#include <SDL3/SDL.h>

#include <memory>
#include <vector>
#include <cstdint>

#include "math.hpp"

class Level
{
public:
	Level();
	Level(int w, int h);

	float width;
	float height;
	float scale;

	vec2<float> f_cursorPosition;
	vec4<float> f_camera;
	vec4<int> rgba_backgroundColor;

	void Update();
	void Render(SDL_Renderer* renderer);
};