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
	SGF::Assets::Font& font = context.fontAssets->Get("ROBOTO_REGULAR_10");

	auto textProperties = [&]()
	{
		SGF::UI::TextProperties props;

		props.font = &font;
		props.color = { 255, 255, 255 };
		props.text = " Developed by Rastislav Madera";

		return props;
	}();


	m_Canvas->AddComponent<SGF::UI::Text>(&textProperties, SGF::UI::Anchor(SGF_Alignment::Center, SGF_Alignment::End, Vector2i(0, 15)));
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

	m_Canvas->Render(renderer);
}