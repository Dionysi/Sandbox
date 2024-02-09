#include "stdfax.h"
#include "Application.h"
#include "Game.h"
#include <chrono>
#include "gui/ImGuiStyle.h"
#include "HighResolutionTimer.h"
#include <IconFontCppHeaders/IconsFontAwesome5.h>


// Initialize static member-variables. 
uint Application::s_RenderWidth = 0;
uint Application::s_RenderHeight = 0;
uint Application::s_WindowWidth = 0;
uint Application::s_WindowHeight = 0;
float Application::s_xContentScale = 1.0f;
float Application::s_yContentScale = 1.0f;

ImGuiContext* Application::s_imContext = nullptr;
bool Application::s_Initialized = false;
GLFWwindow* Application::s_Window = nullptr;
Surface* Application::s_RenderSurface = nullptr;
clContext* Application::s_clContext = nullptr;

int main() {
	Application::Initialize(1024, 1024);
	Application::Run();

	return 0;
}


void Application::Initialize(uint width, uint height)
{
	if (s_Initialized) return;

	// Set the window and render dimensions.
	s_RenderWidth = width, s_WindowWidth = width;
	s_RenderHeight = height, s_WindowHeight = height;

	Application::InitGLFW();
	Application::InitImGui();
	Application::InitOpenCL();
	Input::Initialize(Application::Window());

	JobManager::Initialize();

	s_RenderSurface = new Surface(s_RenderWidth, s_RenderHeight);

	// Set the Game to be initialized.
	s_Initialized = true;

}

void Application::Run()
{
	// Initialize with some default width and height if the app was not yet intialized.
	if (!s_Initialized) Initialize(1024, 1024);

	// Initialize the game. 
	Game game;
	HighResolutionTimer timer;

	while (!glfwWindowShouldClose(Application::Window())) {
		// Compute the time passed since last loop.
		float dt = (float)timer.ElapsedSeconds();
		timer.Restart();

		game.HandleInput(dt);
		game.Tick(dt);
		game.Draw(dt);
		game.RenderGUI(dt);

		// Update the Input singleton.
		Input::Update();

		glfwSwapBuffers(Application::Window());
		glfwPollEvents();
	}

}

void Application::Terminate()
{
	glfwSetWindowShouldClose(s_Window, GLFW_TRUE);
}

GLFWwindow* Application::Window()
{
	return s_Window;
}

Surface* Application::Screen()
{
	return s_RenderSurface;
}

clContext* Application::CLcontext()
{
	return s_clContext;
}

uint Application::WindowWidth()
{
	return s_WindowWidth;
}

uint Application::WindowHeight()
{
	return s_WindowHeight;
}

uint Application::RenderWidth()
{
	return s_RenderWidth;
}

uint Application::RenderHeight()
{
	return s_RenderHeight;
}

float Application::GetContentScaleX()
{
	return s_xContentScale;
}

float Application::GetContentScaleY()
{
	return s_yContentScale;
}

void Application::ResizeRenderSize(unsigned int width, unsigned int height)
{
	delete s_RenderSurface;
	s_RenderSurface = new Surface(width, height);
	s_RenderWidth = width, s_RenderHeight = height;
}

void Application::SetWindowSize(unsigned int width, unsigned int height, bool resetAspectRatio)
{
	// Set aspect ratio.
	if (resetAspectRatio) glfwSetWindowAspectRatio(s_Window, width, height);
	// Set window size.
	glfwSetWindowSize(s_Window, width, height);

	// Reset width and height member variables.
	int w, h; glfwGetWindowSize(s_Window, &w, &h);

	s_WindowWidth = (uint)w, s_WindowHeight = (uint)h;
}

void Application::InitGLFW()
{
	// Initialize glfw.
	glewExperimental = true;

	if (!glfwInit()) FATAL_ERROR("Failed to initialize glfw.");

	// Set the window variables.
	glfwWindowHint(GLFW_SAMPLES, 4);				// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	s_Window = glfwCreateWindow(s_WindowWidth, s_WindowHeight, "Annotation Tool", NULL, NULL);
	if (s_Window == NULL) FATAL_ERROR("Failed to create GLFW window.");

	//glfwSetWindowAspectRatio(s_Window, s_WindowWidth, s_WindowHeight);		// Uncomment to fix aspect ratio.
	glfwSetWindowSizeCallback(s_Window, WINDOW_RESIZE_CALLBACK);
	glfwSetWindowContentScaleCallback(s_Window, WINDOW_CONTENT_SCALE_CALLBACK);

	// Initialize glew.
	glfwMakeContextCurrent(s_Window);

	if (glewInit() != GLEW_OK) FATAL_ERROR("Failed to initialize glew.");

	// Enable OpenGL debug callbacks.
	EnableGLdebugInfo();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	// Set the input modes.
	glfwSetInputMode(s_Window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(s_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSwapInterval(0);
}

void Application::InitImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	s_imContext = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(s_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Enable the docking space for the tool.
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Set the global font-scale based on GLFW's dpi.
	float xscale, yscale;
	glfwGetWindowContentScale(s_Window, &xscale, &yscale);
	io.FontGlobalScale = glm::max(xscale, yscale);
	// Set the global content scale values.
	s_xContentScale = xscale, s_yContentScale = yscale;
	// Update the imgui rounding values.
	ImGui::GetStyle().WindowRounding = 9.0f * glm::max(xscale, yscale);
	ImGui::GetStyle().FrameRounding = 3.0f * glm::max(xscale, yscale);

	float baseFontSize = 13.0f; // 13.0f is the size of the default font. Change to the font size you use.
	float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

	ImFontConfig fontConfig;
	io.Fonts->AddFontDefault(&fontConfig);

	// merge in icons from Font Awesome
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	fontConfig.MergeMode = true;
	fontConfig.PixelSnapH = true;
	fontConfig.GlyphMinAdvanceX = iconFontSize;
	io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, iconFontSize, &fontConfig, icons_ranges);

	fontConfig.MergeMode = true;

	ImGuiEx::AdjustStyleFromHue();
}

void Application::InitOpenCL()
{
	s_clContext = new clContext(true);
}

void Application::WINDOW_RESIZE_CALLBACK(GLFWwindow* window, int width, int height)
{
	// Check if same window, not required but just to be sure.
	if (window != s_Window) return;

	// Resize the viewport.
	glViewport(0, 0, width, height);
	s_WindowWidth = width, s_WindowHeight = height;
}

void Application::WINDOW_CONTENT_SCALE_CALLBACK(GLFWwindow* window, float xscale, float yscale)
{
	// Set the global font scale for ImGui.
	ImGui::GetIO().FontGlobalScale = glm::max(xscale, yscale);
	// Set the global values.
	s_xContentScale = xscale, s_yContentScale = yscale;
}