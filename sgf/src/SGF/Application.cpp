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
	Uint32 timeSinceLastUpdate = 0;
	
	m_Running = true;

	while (m_Running)
	{
		Uint32 elapsedTime = clock.Reset();

		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate >= m_TimePerUpdate)
		{
			double deltaTime = timeSinceLastUpdate / 1000.0;
			timeSinceLastUpdate -= m_TimePerUpdate;

			_HandleEvents();
			_Update(deltaTime);
			_Render();
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
	SDL_RenderPresent(m_Renderer.get());
}