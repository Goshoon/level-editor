#pragma once
#include <cmath>
#include <memory>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
// SDL3
struct SDL_Renderer;
struct SDL_FRect;
// Own
#include "math.hpp"
#include "panel.hpp"
#include "mouseState.hpp"

class Level : public Panel
{
private:
	bool dragging = false;
	vec2<float> f_oldMousePosition;
public:
	Level();
	Level(int w, int h);
	float scale = 1.0f;
	bool grid = true;
	int gridSizeX = 64;
	int gridSizeY = 64;

	vec2<float> f_cursorPosition;
	vec4<float> f_cameraPosition;
	vec4<float> levelPosition;
	vec4<int> rgba_backgroundColor;

	void Update(MouseState& mouse, const SDL_FRect& area);
	void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};