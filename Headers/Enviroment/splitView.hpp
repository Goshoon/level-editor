#pragma once
// Libraries
#include <memory>
// SDL3
#include <SDL3/SDL.h>
// Own
#include "keyboardState.hpp"
#include "mouseState.hpp"
#include "panel.hpp"

class Level;
class AssetManager;

enum ViewMode
{
	DEFAULT,		// Render both views
	TOP_VIEW,		// Render only top view
	BOTTOM_VIEW		// Render only bottom view
};

class SplitView
{
public:
	int tabCooldown = 0;
	float ratio = 0.5f;
	float verticalPadding = 18.0f; // do not render under imgui top bar
	bool dragging = false;
	
	ViewMode viewMode = DEFAULT;
	Level* top = nullptr;
    AssetManager* bottom = nullptr;
    
    SDL_FRect topRect;
	SDL_FRect bottomRect;

    void Update(KeyboardState& keyboard, MouseState& mouse, const SDL_FRect& area);
    void Render(SDL_Renderer* renderer, const SDL_FRect& area);
};