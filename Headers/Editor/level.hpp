#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include <memory>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

#include "math.hpp"
#include "panel.hpp"
#include "mouseState.hpp"

class Level : public Panel
{
private:
	bool dragging = false;
	float gridSize = 64.0f;
	vec2<float> f_oldMousePosition;
public:
	Level();
	Level(int w, int h);
	float scale = 1.0f;
	bool grid = true;

	vec2<float> f_cursorPosition;
	vec4<float> f_cameraPosition;
	vec4<float> levelPosition;
	vec4<int> rgba_backgroundColor;

	void Update(MouseState& mouse, const SDL_FRect& area);
	void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};