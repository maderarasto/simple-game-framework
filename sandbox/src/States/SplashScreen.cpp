#include "sgfpch.h"
#include "SplashScreen.h"

#include "SGF/Structures.h"
#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"
#include "SGF/UI/Canvas.h"
#include "SGF/UI/Text.h"

using namespace States;


SplashScreen::SplashScreen(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{
	SGF::Assets::Font& font = context.fontAssets->Get("ROBOTO_REGULAR_48");

	auto textProperties = [&]()
	{
		SGF::UI::TextProperties props;

		props.position = Vector2i(0, 0);
		props.font = &font;
		props.color = { 255, 255, 255 };
		props.text = "Sandbox";

		return props;
	}();

	m_Canvas->AddComponent<SGF::UI::Text>(&textProperties, { SGF::UI::Alignment::Center, SGF::UI::Alignment::Center });
}


SplashScreen::~SplashScreen()
{

}


bool SplashScreen::HandleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		RequestPopState();
		RequestPushState("GameState");
	}
	
	return true;
}


bool SplashScreen::Update(double deltaTime)
{
	return true;
}


void SplashScreen::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;
	
	m_Canvas->Render(renderer);
}