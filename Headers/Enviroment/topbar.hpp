#pragma once
#include <iostream>
#include "tab.hpp"
#include "panel.hpp"
class Topbar : public Panel
{
public:
	Topbar();
	virtual void Render(SDL_Renderer* renderer, const SDL_FRect& area) = 0;
};