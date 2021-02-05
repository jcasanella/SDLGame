#pragma once

#include "SDL.h"

struct Vector2 {
	float x;
	float y;
};

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
	SDL_Renderer* m_pRenderer;
	bool m_isRunning;
	Vector2 m_paddlePos;
	Vector2 m_ballPos;
};