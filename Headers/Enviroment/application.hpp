#pragma once
#include <iostream>
#include <utility>
#include <SDL3/SDL.h>

#include "enums.hpp"
#include "level.hpp"
#include "splitView.hpp"
#include "math.hpp"
#include "mouseState.hpp"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

class Application
{
private:
	Application();											// Initialization of Inputs, Window and Renderer
	Application(const Application&) = delete;
  	Application& operator=(const Application&) = delete;

  	SDL_FRect windowArea = { 0.0f, 0.0f, 1920.0f, 1080.0f };
  	SplitView splitView;
	MouseState mouse;

	void InitSDL();
	void InitImgui();
	void UserInterface();
	void CreateContext();
	void InputReleased(SDL_Event* event);
	void InputPressed(SDL_Event* event);
public:
	static Application& GetInstance()
	{
		static Application instance;
    	return instance;
	}

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool done = false;

	void Update();
	void Input();
	void Display();
	void DrawEverything();
	void Quit();

	// Level Manager
	std::shared_ptr<Level> currentLevel = nullptr;
};