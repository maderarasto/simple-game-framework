#include "sgfpch.h"
#include "GameState.h"

#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"
#include "SGF/UI/Canvas.h"

using namespace States;


GameState::GameState(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{
	SGF::Assets::Image& image = context.imageAssets->Get("PLAYER");
	SGF::Assets::Font& font = context.fontAssets->Get("ROBOTO_REGULAR_10");

	m_Mob = std::make_unique<SGF::EntitySystem::Mob>(Vector2f(480, 648), Vector2f(64, 64), image);

	SGF::UI::TextPtr text = std::make_unique<SGF::UI::Text>(Vector2i(512, 384), font, "Simple Game Framework");
	text->SetColor({ 255, 255, 255 });
}


GameState::~GameState()
{

}


bool GameState::HandleEvent(SDL_Event& event)
{
	return true;
}


bool GameState::Update(double deltaTime)
{
	m_Mob->SetVelocity(Vector2f(0.f, -1.f * 50 * deltaTime));
	m_Mob->Update(deltaTime);
	
	return true;
}


void GameState::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;

	m_Canvas->Render(renderer);
}