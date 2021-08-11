#include "sgfpch.h"
#include "GameState.h"

#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"
#include "SGF/UI/Canvas.h"
#include "SGF/UI/Structures.h"

using namespace States;


GameState::GameState(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{
	m_CommandQueue = std::make_unique<SGF::Core::CommandQueue>();
	m_PlayerController = std::make_unique<SGF::Core::PlayerController>();
	m_Player = std::make_unique<Entities::Player>(Vector2f(480, 640), Vector2f(64, 64), context.imageAssets->Get("PLAYER"));
}


GameState::~GameState()
{

}


bool GameState::HandleEvent(SDL_Event& event)
{
	m_Canvas->HandleEvent(event);

	return true;
}


bool GameState::Update(double deltaTime)
{	
	m_PlayerController->HandleRealtimeInput(*m_CommandQueue);
	m_Canvas->Update(deltaTime);

	while (!m_CommandQueue->IsEmpty())
	{
		SGF::Core::Command command = m_CommandQueue->Pop();
		m_Player->OnCommand(command);
	}

	m_Player->Update(deltaTime);

	return true;
}


void GameState::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	m_Player->Render(renderer);

	m_Canvas->Render(renderer);
}