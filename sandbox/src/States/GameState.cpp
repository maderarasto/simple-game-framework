#include "sgfpch.h"
#include "GameState.h"

using namespace States;


GameState::GameState(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{

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
	return true;
}


void GameState::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}