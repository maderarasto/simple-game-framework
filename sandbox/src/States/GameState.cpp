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

	auto buttonProps = [&]()
	{
		SGF::UI::ButtonProperties props;

		props.font = &context.fontAssets->Get("ROBOTO_REGULAR_24");
		props.text = "Button";
		props.onClick = [&]() {};

		return props;
	}();


	m_Canvas->AddComponent<SGF::UI::Text>(&textProperties, SGF::UI::Anchor(SGF_Alignment::Center, SGF_Alignment::End, Vector2i(0, 15)));
	m_Canvas->AddComponent<SGF::UI::Button>(&buttonProps, SGF::UI::Anchor(SGF_Alignment::Center, SGF_Alignment::Center));
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
	m_Canvas->Update(deltaTime);

	return true;
}


void GameState::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	m_Canvas->Render(renderer);
}