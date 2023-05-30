#include "stdfax.h"
#include "Game.h"

Game::Game()
{
	// Call your initializers from the constructor.
}

Game::~Game()
{
	// Perform any saving operations and free allocated memory.
}

void Game::Tick(float dt)
{
	// Update average frametime.
	m_AvgFrameTime = 0.99f * m_AvgFrameTime + 0.01 * dt;

	// Game logic goes here.

}

void Game::Draw(float dt)
{
	// Rendering goes here.

	Application::Screen()->SyncPixels();
}

void Game::RenderGUI(float dt)
{
	// GUI code goes here. 

	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const static char* windowTitle = "Debug";
	static bool display = true;
	ImGui::Begin(windowTitle, &display, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(1.25f);
	ImGui::Text("Frame-time: %.1f", dt * 1000.0f);
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
