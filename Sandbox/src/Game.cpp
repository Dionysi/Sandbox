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
		ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus))
	{

		// Create docking space.
		ImGuiID dockspaceID = ImGui::GetID("main_dock");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f),
			ImGuiDockNodeFlags_::ImGuiDockNodeFlags_None);

		// Main menu bar.
		if (ImGui::BeginMainMenuBar())
		{
			// File IO menu functions.
			if (ImGui::BeginMenu("\xef\x85\x9b File")) // "ICON_FA_FILE File"
			{
				// Menu item for loading projects.
				bool itemClicked = false;
				if (ImGui::MenuItem("\xef\x80\x91 Exit", "Ctrl+W", &itemClicked)) // "ICON_FA_POWER_OFF Exit"
				{
					Application::Terminate();
				}

				ImGui::EndMenu();
			}

			// View menu.
			if (ImGui::BeginMenu("\xef\x81\xae View")) // "ICON_FA_EYE View"
			{
				// Toggle displaying the debug window.
				if (ImGui::MenuItem("\xef\x86\x88 Debug", "Ctrl+Alt+D", &m_DisplayDebugWindow, true)) // "ICON_FA_BUG Debug"
				{

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
	ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_None | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse;
	ImTextureID textureID = (void*)Application::Screen()->GetRenderTexture();

	if (ImGui::Begin("viewport", NULL, flags))
	{
		// Size of the window in pixels.
		ImVec2 canvasSize = ImGui::GetContentRegionAvail();
		// Position of the window in pixel space.
		ImVec2 canvasPos = ImGui::GetCursorScreenPos();

		// Fetch the drawing list for the current ImGui window to which we are going to add.
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		// ImGUI's user input.
		ImGuiIO& io = ImGui::GetIO();
		// ImGui style values.
		ImGuiStyle& style = ImGui::GetStyle();

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

		drawList->AddImage(textureID, canvasPos + pSize, canvasPos + pSize + wSize);
	}
	ImGui::End();
}

void Game::guiDebugWindow(float dt)
{
	// Do not display the debug window when the user closes it.
	if (!m_DisplayDebugWindow) return;

	if (ImGui::Begin("Debug", &m_DisplayDebugWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
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

void Game::HandleInput(float dt)
{
	// Modifier keys.
	bool modAlt = Input::KeyDown(Key::LeftAlt) || Input::KeyDown(Key::RightAlt);
	bool modCtrl = Input::KeyDown(Key::LeftControl) || Input::KeyDown(Key::RightControl);

	// Ctrl+W.
	if (Input::KeyPressed(Key::W) && modCtrl)
	{
		Application::Terminate();
	}

	// Ctrl+Alt+D
	if (Input::KeyPressed(Key::D) && modCtrl && modAlt)
	{
		m_DisplayDebugWindow = !m_DisplayDebugWindow;
	}
}
