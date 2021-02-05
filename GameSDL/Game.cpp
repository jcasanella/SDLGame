#include "Game.h"

const int THICKNESS = 15;
const int HALF_THICKNESS = THICKNESS / 2;

Game::Game(): m_pWindow(nullptr), m_pRenderer(nullptr), m_isRunning(true)
{
	m_ballPos = { 1024 / 2, 768 / 2 };
	m_paddlePos = { 10.0f, 768 / 2 };
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

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_pRenderer) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(m_pRenderer);
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
	// Clear the back buffer 
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderClear(m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

	// Build rectangle to draw
	// top rectangle
	SDL_Rect top_wall;
	top_wall.x = 0;
	top_wall.y = 0;
	top_wall.w = 1024;
	top_wall.h = THICKNESS;
	SDL_RenderFillRect(m_pRenderer, &top_wall);

	// bottom rectangle
	SDL_Rect bottom_wall;
	bottom_wall.x = 0;
	bottom_wall.y = 768 - THICKNESS;
	bottom_wall.w = 1024;
	bottom_wall.h = THICKNESS;
	SDL_RenderFillRect(m_pRenderer, &bottom_wall);

	// right wall
	SDL_Rect right_wall;
	right_wall.x = 1024 - THICKNESS;
	right_wall.y = 0;
	right_wall.w = THICKNESS;
	right_wall.h = 1024;
	SDL_RenderFillRect(m_pRenderer, &right_wall);

	// draw ball
	SDL_Rect ball{
		static_cast<int>(m_ballPos.x - HALF_THICKNESS),
		static_cast<int>(m_ballPos.y - HALF_THICKNESS),
		THICKNESS,
		THICKNESS
	};
	SDL_RenderFillRect(m_pRenderer, &ball);


	// swap back buffer to front buffer
	SDL_RenderPresent(m_pRenderer);
}