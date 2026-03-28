#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <SDL3/SDL.h>

#include "math.hpp"
#include "enums.hpp"
#include "splitView.hpp"
#include "mouseState.hpp"
#include "editingBound.hpp"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

class Application
{
private:
  	// Inputs and window data
  	SDL_FRect windowArea = { 0.0f, 0.0f, 1920.0f, 1080.0f };
	MouseState mouse;

	// Panel manager
	SplitView splitView;

	// Level Manager
	std::vector<EditingBound> editingBounds;
	EditingBound* currentBound = nullptr;

	bool createWindow = false;

	void InitSDL();
	void InitImgui();
	void UserInterface();
	void CreateContext();
	void InputReleased(SDL_Event* event);
	void InputPressed(SDL_Event* event);
	void NewLevel(const std::string& name, int width, int height);
public:
	Application();	// Initialization of Inputs, Window and Renderer
	~Application();

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool done = false;

	void Update();
	void Input();
	void Display();
	void DrawEverything();
	void Quit();
};