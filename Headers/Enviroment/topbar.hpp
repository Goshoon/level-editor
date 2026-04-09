#pragma once
// Libraries
#include <iostream>
//SDL3
struct SDL_Texture;
// Own
#include "tab.hpp"
#include "panel.hpp"
struct MouseState;

struct Button
{
	SDL_Texture* image;
	vec4<float> src;
	vec4<float> dst;
};

class Topbar
{
private:
	vec2<float> windowRes;
public:
	Topbar();
	void Update();
	void Render(SDL_Renderer* renderer);

	Panel* panel = nullptr;
	Button displayButton;
	SDL_FRect* resolution = nullptr;
	MouseState* mouse = nullptr;

	bool showContent = false;
};