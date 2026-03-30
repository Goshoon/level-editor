#pragma once
// Libraries
#include <vector>
#include <string>
// Interface SDL3
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Cursor;
struct SDL_FRect;
union SDL_Event;
// Own
#include "splitView.hpp"
#include "mouseState.hpp"
#include "editingBound.hpp"

class Application
{
private:
  	// Inputs and window data
  	SDL_Cursor* cursor = nullptr;
  	SDL_FRect windowArea;

	// Panel manager
	SplitView splitView;
	MouseState mouse;

	// Level Manager
	std::vector<EditingBound> editingBounds;
	EditingBound* currentBound = nullptr;

	bool gridWindow = false;
	bool createWindow = false;
	bool grid = true;

	void InitSDL();
	void InitImgui();
	void UserInterface();
	void CreateContext();
	void InputReleased(SDL_Event* event);
	void InputPressed(SDL_Event* event);
	void NewLevel(const std::string& name, int width, int height);
	void CloseAllLevels();
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