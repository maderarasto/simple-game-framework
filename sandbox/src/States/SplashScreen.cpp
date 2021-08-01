#include "sgfpch.h"
#include "SplashScreen.h"

#include "SGF/Structures.h"
#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"

using namespace States;


SplashScreen::SplashScreen(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{
	SGF::Assets::Font& font = context.fontAssets->Get("ROBOTO_REGULAR_18");

	/*m_Title = std::make_unique<SGF::UI::Text>(Vector2i(512, 384), font, "Sandbox");
	m_Title->SetColor({ 255, 255, 255 });*/
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
	
	//m_Title->Render(renderer);
}