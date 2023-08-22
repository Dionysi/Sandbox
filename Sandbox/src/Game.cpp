#include "stdfax.h"
#include "Game.h"

void Game::guiMainDockingWindow()
{
	// Properties for main docking window.
	ImGui::SetWindowPos("main", ImVec2(0.0f, 0.0f));
	ImGui::SetWindowSize("main", ImVec2(Application::WindowWidth(), Application::WindowHeight()));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	// Begin docking window.
	if (ImGui::Begin("main", NULL,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
		//ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration |				// Do not use because docked windows are under the menu bar.
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus);

		ImGuiID dockspaceID = ImGui::GetID("main_dock");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f),
			ImGuiDockNodeFlags_::ImGuiDockNodeFlags_None
		))
	{
		// Main menu bar.
		if (ImGui::BeginMainMenuBar())
		{
			// File IO menu functions.
			if (ImGui::BeginMenu("File"))
			{
				// Menu item for loading projects.
				bool itemClicked = false;
				if (ImGui::MenuItem("Exit", "Esc", &itemClicked))
				{
					Application::Terminate();
				}

				ImGui::EndMenu();
			}


			ImGui::EndMainMenuBar();
		}
	}

	ImGui::End();
	ImGui::PopStyleVar(2);
}

void Game::guiViewportWindow()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_None | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse;
	ImTextureID textureID = (void*)Application::Screen()->GetRenderTexture();

	if (ImGui::Begin("viewport", NULL, flags))
	{
		// Size of the window in pixels.
		ImVec2 canvasSize = ImGui::GetContentRegionAvail();
		// Position of the window in pixel space.
		ImVec2 canvasPos = ImGui::GetCursorScreenPos();

		// Render size. 
		ImVec2 textureSize(Application::RenderWidth(), Application::RenderHeight());

		// Calculate the scale at which we display the image.
		ImVec2 textureScale = canvasSize / textureSize;
		// Get the smallest of the two. 
		float scale = glm::min(textureScale.x, textureScale.y);

		// Window & render size.
		ImVec2 wSize(Application::RenderWidth() * scale, Application::RenderHeight() * scale);
		// Padding on the left of the image.
		ImVec2 pSize = (canvasSize - wSize) / 2;

		ImGui::BeginGroup();
		ImGui::PushStyleColor(ImGuiCol_FrameBg, 0xFF000000);

		// Padding window.
		ImGui::BeginChildFrame(ImGui::GetID("padding_render_window"), pSize);
		ImGui::EndChildFrame();

		// Create a child window in the middle of the screen.
		if (textureScale.x > textureScale.y) ImGui::SameLine(0.0f, 0.0f);
		ImGui::BeginChildFrame(ImGui::GetID("render_child_window"), wSize, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
		ImGui::Image(textureID, wSize);
		ImGui::EndChildFrame();


		ImGui::EndGroup();
		ImGui::PopStyleColor();
	}

	ImGui::End();
	ImGui::PopStyleVar(2);
}

void Game::guiDebugWindow(float dt)
{
	const static char* windowTitle = "Debug";
	static bool display = true;
	if (ImGui::Begin(windowTitle, &display, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::SetWindowFontScale(1.25f);
		ImGui::Text("Frame-time: %.1f", dt * 1000.0f);
		ImGui::Text("Avg ft: %.1f", m_AvgFrameTime * 1000.0f);
	}
	ImGui::End();
}

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

	/* Create the main docking window. */
	guiMainDockingWindow();
	/* Create an ImGui window that renders an OpenGL texture only. */
	guiViewportWindow();
	/* Create basic debug information window. */
	guiDebugWindow(dt);

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
