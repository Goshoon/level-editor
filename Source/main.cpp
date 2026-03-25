#include <iostream>
#include "imgui.h"
#include "application.hpp"

// color palette: https://coolors.co/palette/f8f9fa-e9ecef-dee2e6-ced4da-adb5bd-6c757d-495057-343a40-212529

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

		// Draw Methods
		application.Display();
		application.DrawEverything();
	}

	Application::GetInstance().Quit();
	return 0;
}