#pragma once

#include "SDL.h"

class Game {
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* m_pWindow;
	bool m_isRunning;
};