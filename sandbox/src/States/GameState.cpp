#include "sgfpch.h"
#include "GameState.h"

#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"
#include "SGF/UI/Canvas.h"
#include "SGF/UI/Structures.h"

#include "SGF/EntitySystem/Mob.h"

using namespace States;


GameState::GameState(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{
	m_CommandQueue = std::make_unique<SGF::Core::CommandQueue>();
	m_PlayerController = std::make_unique<SGF::Core::PlayerController>();
	m_Physics = std::make_unique<SGF::EntitySystem::Physics>(m_Entities);

	auto mob1 = std::make_unique<SGF::EntitySystem::Mob>(Vector2f(480, 64), Vector2f(64, 64), context.imageAssets->Get("PLAYER"));
	auto player = std::make_unique<Entities::Player>(Vector2f(480, 640), Vector2f(64, 64), context.imageAssets->Get("PLAYER"));

	mob1->SetCollider(mob1->GetPosition(), mob1->GetSize());
	player->SetCollider(player->GetPosition(), player->GetSize());

	m_Player = player.get();
	m_Entities.push_back(std::move(mob1));
	m_Entities.push_back(std::move(player));
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

	m_Physics->HandleCollisions();

	for (auto& entity : m_Entities)
	{
		entity->Update(deltaTime);
	}

	return true;
}


void GameState::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	for (auto& entity : m_Entities)
	{
		entity->Render(renderer);
	}

	m_Canvas->Render(renderer);
}