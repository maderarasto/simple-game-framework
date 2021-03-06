#include "sgfpch.h"
#include "Application.h"

#include "SGF/Core/Logger.h"
#include "SGF/Core/Clock.h"
#include "SGF/Core/Keyboard.h"

#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"
#include "SGF/States/StateStack.h"

using namespace SGF;


Application::Application(AppConfig* config)
{
	Core::Logger::Init();
	Core::Keyboard::Init();
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL2 library initialization failed!");
	CORE_LOG_TRACE("SDL2 library successfully initialized.");

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
		throw std::runtime_error("SDL2_image library initialization failed!");
	CORE_LOG_TRACE("SDL2_image library successfully initialized.");
	
	if (TTF_Init() < 0)
		throw std::runtime_error("SDL2_TTF library initialization failed!");
	CORE_LOG_TRACE("SDL2_TTF library successfully initialized.");

	CORE_LOG_INFO("Resolution: {}x{}", config->resolution_width, config->resolution_height);

	m_Window = SDL_WindowPtr(
		SDL_CreateWindow(config->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config->resolution_width, config->resolution_height, NULL)
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

	m_ImageAssets = std::make_unique<ImageManager>();
	m_FontAssets = std::make_unique<FontManager>();

	States::Context context = States::Context(
		m_Renderer.get(),
		m_ImageAssets.get(),
		m_FontAssets.get()
	);

	m_StateStack = std::make_unique<States::StateStack>(context);

	SetFrameRate(60.0);

	CORE_LOG_INFO("INFO");
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
		}
	}
}


void Application::_HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != NULL)
	{
		m_StateStack->HandleEvent(event);
		
		if (m_StateStack->IsEmpty() || event.type == SDL_QUIT)
			m_Running = false;
	}
}


void Application::_Update(double deltaTime)
{
	KEYBOARD::HandleRealtimeInput();
	m_StateStack->Update(deltaTime);
}


void Application::_Render()
{
	SDL_RenderClear(m_Renderer.get());
	m_StateStack->Render();
	SDL_RenderPresent(m_Renderer.get());
}