#pragma once
/*
	The application class is pretty much the main class of this program,
	everything and i mean EVERYTHING runs from here.

	Then it follows this structure: 
		Application -> SplitView -> Level / Asset editor -> Contents

	Be aware that this program is divided into two different panels at
	all times.
*/
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
	bool hideMenuBar = false;
	bool grid = true;
	short boundIndex = 1;
	
	// Run at the start
	bool InitSDL();
	bool InitImgui();
	bool CreateContext();

	// Regular methods
	void UserInterface();
	void InputReleased(SDL_Event* event);
	void InputPressed(SDL_Event* event);

	// Level handling
	void NewLevel(const std::string& name, int width, int height);
	void CloseCurrentLevel();
	void CloseAllLevels();
public:
	Application();	// Initialization of Inputs, Window and Renderer
	~Application();

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool done = false;


	void Update();
	void Input(); // Get all app inputs
	void Display(); // Clear display
	void DrawEverything(); // Render in order
	void Quit(); // Closing the pogram...
};