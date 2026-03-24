#include <iostream>
#include "imgui.h"
#include "application.hpp"

int main(int argc, char* argv[])
{
	while (!Application::GetInstance().done)
	{
		Application& application = Application::GetInstance(); // Get reference to application

		// Update methods
		application.Input();

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		application.Update();

		if (application.currentLevel != nullptr)
			application.currentLevel->Update();

		// Draw Methods
		application.Display();

		if (application.currentLevel != nullptr)
			application.currentLevel->Render(application.renderer);

		application.DrawEverything();
	}

	Application::GetInstance().Quit();
	return 0;
}