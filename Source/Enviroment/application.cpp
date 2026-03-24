#include "application.hpp"

Application::Application()
{
	// Setup Platform/Renderer backends
	window = nullptr;
	renderer = nullptr;

	InitSDL();
	CreateContext();
	InitImgui();

	currentLevel = std::make_unique<Level>(640, 640); // MAKING A TEST LEVEL
}

void Application::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
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
}

void Application::Display() 
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Application::DrawEverything()
{
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_RenderPresent(renderer);
}

void Application::Input()
{
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
			case SDL_EVENT_MOUSE_MOTION:
			{
				/*
        		SDL_GetMouseState(&mPosition.x, &mPosition.y);
        		mPosition.x /= (int)RENDER_SCALE;
        		mPosition.y /= (int)RENDER_SCALE;
        		*/
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
				/*
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						mbLeft = true;
					}
					break;
					case SDL_BUTTON_RIGHT:
					{
						mbRight = true;
					}
					break;
				}
				*/
			}
			break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				/*
				mbLeft = false;
				mbRight = false;
				*/
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
		if (ImGui::MenuItem("New")) {}
    	if (ImGui::MenuItem("Save")) {}
    	if (ImGui::MenuItem("Load")) {}
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
    	ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

void Application::Quit()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	SDL_Quit();
}