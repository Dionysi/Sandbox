#pragma once
#include "Template/Application.h"

class Game
{

public:
	Game();
	void Tick(float dt);
	void Draw(float dt);
	void RenderGUI(float dt);
};

