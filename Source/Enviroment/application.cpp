#include "application.hpp"
// Libraries
#include <iostream>
#include <utility>
#include <algorithm>
// SDL3
#include <SDL3/SDL.h>
// Imgui
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
// Own
#include "enums.hpp"

Application::Application()
{
	// Setup Platform/Renderer backends
	window = nullptr;
	renderer = nullptr;

	InitSDL();
	CreateContext();
	InitImgui();
}

Application::~Application()
{
	delete currentBound;
}

void Application::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	SDL_SetCursor(cursor);
}

void Application::InitImgui()
{
	// IMGUI initialization
	IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void Application::CreateContext()
{
	// SDL initialization
	window = SDL_CreateWindow(
		APPLICATION_NAME,
		APPLICATION_WIDTH, APPLICATION_HEIGHT, 
		SDL_WINDOW_RESIZABLE
	);

	if (!window)
	{
		std::cout << "Window creation error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, nullptr);

	if (!renderer)
	{
		std::cout << "Renderer creation error: " << SDL_GetError() << std::endl;
	}
}

void Application::Update() 
{
	UserInterface();

	// Get Window resolution updated
	int winW = 0, winH = 0;
	SDL_GetWindowSize(window, &winW, &winH);
	windowArea.x = 0;
	windowArea.y = 0;
	windowArea.w = static_cast<float>(winW);
	windowArea.h = static_cast<float>(winH);

	if (currentBound != nullptr)
	{
		splitView.top = currentBound->level.get();
		splitView.bottom = currentBound->assetManager.get();
		splitView.Update(mouse, windowArea);
		currentBound->level->Update(mouse, splitView.topRect);
	}

	if (editingBounds.size() == 1) // if only one element, always focus on the only
		currentBound = &editingBounds.front();
}

void Application::Display() 
{
    SDL_RenderClear(renderer);
}

void Application::DrawEverything()
{
	// Bug: Using the ImGui context makes the level dissapear
	if (currentBound != nullptr)
		splitView.Render(renderer, windowArea);
	
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

	SDL_SetRenderDrawColor(renderer, 33, 37, 41, 255);
	SDL_RenderPresent(renderer);
}

void Application::Input()
{
	mouse.mouseWheelUp = false;
	mouse.mouseWheelDown = false;

	SDL_Event event;
	while ( SDL_PollEvent(&event))
	{
		ImGui_ImplSDL3_ProcessEvent(&event);
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
			{
				done = true;
			}
			break;
			case SDL_EVENT_MOUSE_WHEEL:
			{
				if (event.wheel.y > 0) // mouse wheel up
				{
					mouse.mouseWheelUp = true;
					mouse.mouseWheelDown = false;
				}
				else if (event.wheel.y < 0) // mouse wheel up
				{
					mouse.mouseWheelUp = false;
					mouse.mouseWheelDown = true;
				}
			}
			break;
			case SDL_EVENT_MOUSE_MOTION:
			{
        		SDL_GetMouseState(&mouse.f_mousePosition.x, &mouse.f_mousePosition.y);
    		}
      		break;
			case SDL_EVENT_KEY_DOWN:
			{
				InputPressed(&event);
			}
			break;
			case SDL_EVENT_KEY_UP:
			{
				InputReleased(&event);
			}
			break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			{
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						mouse.mouseButtonLeft = true;
					}
					break;
					case SDL_BUTTON_RIGHT:
					{
						mouse.mouseButtonRight = true;
					}
					break;
				}
			}
			break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				mouse.mouseButtonLeft = false;
				mouse.mouseButtonRight = false;
			}
			break;
        }
    }
}

void Application::InputReleased(SDL_Event* event) {}
void Application::InputPressed(SDL_Event* event) {}

void Application::UserInterface()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New")) createWindow = true;
    	if (ImGui::MenuItem("Save")) {}
    	if (ImGui::MenuItem("Load")) {}
    	ImGui::Separator();
    	if (ImGui::MenuItem("Close all")) CloseAllLevels();
    	ImGui::Separator();
    	if (ImGui::MenuItem("Exit")) done = true;

    	ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
	{
    	ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Assets"))
	{
		if (ImGui::MenuItem("Create object")) {}
		if (ImGui::MenuItem("Create Tileset")) {}
    	ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("grid"))
		{
			if (gridWindow)
			{
				gridWindow = false;
			}
			else
			{
				gridWindow = true;
			}
		}
    	ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    if (gridWindow)
    {
    	static int width  = 256;
    	static int height = 256;
    	ImGui::Begin("Grid options", nullptr);
    	ImGui::Text("Grid options");
    	ImGui::Checkbox("Grid", &currentBound->level->grid);
    	// ---- Size Inputs
    	ImGui::Text("Size");
    	
    	ImGui::Text("Width");
    	ImGui::SameLine();
    	ImGui::SetNextItemWidth(80);
    	ImGui::InputInt("##Width", &currentBound->level->gridSizeX);
	
    	ImGui::SameLine();
    	
    	ImGui::Text("Height");
    	ImGui::SameLine();
    	ImGui::SetNextItemWidth(80);
    	ImGui::InputInt("##Height", &currentBound->level->gridSizeY);
    	ImGui::End();
    }

    if (createWindow)
	{
		static char useName[32] = "";
    	static bool useTilesets = true;
    	static bool useObjects  = true;
    	static int width  = 256;
    	static int height = 256;
	
    	ImGuiIO& io = ImGui::GetIO();
	
    	ImVec2 windowSize = ImVec2(360, 240);
	
    	ImGui::SetNextWindowPos(
    	    ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
    	    ImGuiCond_Always,
    	    ImVec2(0.5f, 0.5f)
    	);
	
    	ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
	
    	ImGuiWindowFlags flags =
    	    ImGuiWindowFlags_NoResize |
    	    ImGuiWindowFlags_NoCollapse |
    	    ImGuiWindowFlags_NoMove;
	
    	ImGui::Begin("Create Level", nullptr, flags);
	
    	// Level name
    	ImGui::Text("Level name");
    	ImGui::SameLine();
    	ImGui::SetNextItemWidth(-1);
    	ImGui::InputText("##LevelName", useName, sizeof(useName));
	
    	ImGui::Spacing();
	
    	// Size inputs
    	ImGui::Text("Size");
    	
    	ImGui::Text("Width");
    	ImGui::SameLine();
    	ImGui::SetNextItemWidth(80);
    	ImGui::InputInt("##Width", &width);
	
    	ImGui::SameLine();
    	
    	ImGui::Text("Height");
    	ImGui::SameLine();
    	ImGui::SetNextItemWidth(80);
    	ImGui::InputInt("##Height", &height);
	
    	// Clamp values
    	width  = std::clamp(width,  64, 6000);
    	height = std::clamp(height, 64, 6000);
	
    	ImGui::Spacing();
	
    	ImGui::Text("Assets types used:");
    	ImGui::Checkbox("Tilesets", &useTilesets);
    	ImGui::Checkbox("Objects", &useObjects);
	
    	ImGui::Spacing();
    	ImGui::Separator();
    	ImGui::Spacing();
	
    	float buttonWidth = 80.0f;
    	float spacing = ImGui::GetStyle().ItemSpacing.x;
    	float totalWidth = buttonWidth * 2 + spacing;
	
    	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - totalWidth) * 0.5f);
    	if (ImGui::Button("Create", ImVec2(buttonWidth, 0)))
    	{
    	    // Prevent it if nothing is selected
    	    if (useTilesets || useObjects)
    	    {
    	    	NewLevel(useName, width, height);
    	        createWindow = false;
    	    }
    	}
	
    	ImGui::SameLine();
	
    	if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
    	{
    	    createWindow = false;
    	}
	
    	if (!useTilesets && !useObjects)
		{
    		ImGui::TextColored(ImVec4(1,0,0,1), "Select at least one type");
		}
	
    	ImGui::End();
	}
}

void Application::Quit()
{
	SDL_DestroyCursor(cursor);
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	SDL_Quit();
}

void Application::NewLevel(const std::string& name, int width, int height)
{
	editingBounds.emplace_back(name, width, height);
}

void Application::CloseAllLevels()
{
	splitView.top = nullptr;
	splitView.bottom = nullptr;
	currentBound = nullptr;
	editingBounds.clear();
}