#include "stdfax.h"
#include "Game.h"

void Game::Tick(float dt)
{
	int third = Application::RenderHeight() / 3;
	for (int y = 0; y < third; y++)
		for (int x = 0; x < Application::RenderWidth(); x++)
			Application::RenderSurface()->PlotPixel(Color(1.0f, 0.0f, 0.0f), x, y);

	for (int y = third; y < 2 * third; y++)
		for (int x = 0; x < Application::RenderWidth(); x++)
			Application::RenderSurface()->PlotPixel(Color(0.0f, 1.0f, 0.0f), x, y);

	for (int y = 2 * third; y < Application::RenderHeight(); y++)
		for (int x = 0; x < Application::RenderWidth(); x++)
			Application::RenderSurface()->PlotPixel(Color(0.0f, 0.0f, 1.0f), x, y);

}

void Game::Draw(float dt)
{
	Application::RenderSurface()->SyncPixels();
}

void Game::RenderGUI(float dt)
{	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const static char* windowTitle = "Debug";
	static bool display = true;
	ImGui::Begin(windowTitle, &display, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(1.5f);
	ImGui::Text("Frame-time: %.1f", dt * 1000.0f);
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
