#pragma once
#include "template/Application.h"

/*
* Implement your game logic in this class. The order of function calls is:
* 1) Tick
* 2) Draw
* 3) RenderGUI
*/
class Game
{

private:

	/*
	* Average time it takes to process a frame.
	* For debugging purpose only.
	*/
	float m_AvgFrameTime = 0.0f;

	/*
	* Creates the main docking window.
	*/
	void guiMainDockingWindow();
	/*
	* Creates the viewport window for rendering the OpenGL texture.
	*/
	void guiViewportWindow();
	/*
	* Creates the debug information window.
	* @param[in] dt			Time since previous update in seconds.
	*/
	void guiDebugWindow(float dt);

public:
	/*
	* Call your initializers from the constructor.
	*/
	Game();
	/*
	* Perform any saving operations and free allocated memory.
	*/
	~Game();

	/*
	* Use the Tick function to implement your game logic.
	* @param[in] dt				Time since previous Tick call in seconds.
	*/
	void Tick(float dt);
	/*
	* Use the draw function to implement any non-gui related rendering.
	* @param[in] dt				Time since previous call in seconds.
	*/
	void Draw(float dt);
	/*
	* Use the render gui function to implement any gui related rendering using ImGui.
	* @param[in] dt				Time since previous call in seconds.
	*/
	void RenderGUI(float dt);
};

