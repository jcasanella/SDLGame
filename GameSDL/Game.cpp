#include "Game.h"

Game::Game()
{
	m_pWindow = NULL;
	m_isRunning = true;
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Replace 0 for the flags - SDL_WINDOW_FULLSCREEN, SDL_WINDOW_OPENGL, SDL_WINDOW_RESIZABLE
	m_pWindow = SDL_CreateWindow("Game Programming", 100, 100, 1024, 768, 0);
	if (!m_pWindow) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (m_isRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;

	// While events to process...
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		}
	}

	// Check if Esc pressed
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_isRunning = false;
	}
}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{

}