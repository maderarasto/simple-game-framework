#include "Application.h"
#include "SGF/Core/Logger.h"
#include "SGF/Core/Clock.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace SGF;


Application::Application()
{
	Core::Logger::Init();
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL2 library initialization failed!");
	CORE_LOG_TRACE("SDL2 library successfully initialized.");

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
		throw std::runtime_error("SDL2_image library initialization failed!");
	CORE_LOG_TRACE("SDL2_image library successfully initialized.");
	
	if (TTF_Init() < 0)
		throw std::runtime_error("SDL2_TTF library initialization failed!");
	CORE_LOG_TRACE("SDL2_TTF library successfully initialized.");

	m_Window = SDL_WindowPtr(
		SDL_CreateWindow("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, NULL)
	);

	if (!m_Window)
		throw std::runtime_error("SDL window initialization failed!");
	CORE_LOG_INFO("SDL window successfully initialized.");

	m_Renderer = SDL_RendererPtr(
		SDL_CreateRenderer(m_Window.get(), 0, NULL)
	);

	if (!m_Renderer)
		throw std::runtime_error("SDL renderer initialization failed!");
	CORE_LOG_INFO("SDL renderer successfully initialized.");

	SetFrameRate(60.0);
}


Application::~Application()
{

}


void Application::SetFrameRate(double frameRate)
{
	m_TimePerUpdate = 1000.0 / frameRate;
}


void Application::Run()
{
	Core::Clock clock;

	Uint32 currentFrames = 0;
	Uint32 timeSinceLastUpdate = 0;
	Uint32 timeSinceLastFpsCount = 0;
	
	m_Running = true;

	while (m_Running)
	{
		Uint32 elapsedTime = clock.Reset();

		timeSinceLastUpdate += elapsedTime;
		timeSinceLastFpsCount += elapsedTime;

		while (timeSinceLastUpdate >= m_TimePerUpdate)
		{
			double deltaTime = timeSinceLastUpdate / Core::Clock::OneSecond;
			
			timeSinceLastUpdate -= m_TimePerUpdate;
			currentFrames++;

			_HandleEvents();
			_Update(deltaTime);
			_Render();


		}

		if (timeSinceLastFpsCount >= Core::Clock::OneSecond)
		{
			timeSinceLastFpsCount = 0;
			m_FpsCount = currentFrames;
			currentFrames = 0;

			CORE_LOG_TRACE("FPS: {}", m_FpsCount);
		}
	}
}


void Application::_HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != NULL)
	{
		if (event.type == SDL_QUIT)
			m_Running = false;
	}
}


void Application::_Update(double deltaTime)
{

}


void Application::_Render()
{
	SDL_RenderClear(m_Renderer.get());

	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 10);
	SDL_Color fontColor = { 255, 255, 255 };

	std::string text = "FPS: " + std::to_string(m_FpsCount);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_Renderer.get(), textSurface);
	SDL_Rect textRect = { 10, 10, 35, 12 };

	SDL_RenderCopy(m_Renderer.get(), textTexture, NULL, &textRect);
	SDL_RenderPresent(m_Renderer.get());
}