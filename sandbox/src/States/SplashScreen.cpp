#include "sgfpch.h"
#include "SplashScreen.h"

#include "SGF/Structures.h"
#include "SGF/Assets/Asset.h"
#include "SGF/Assets/AssetManager.h"

using namespace States;


SplashScreen::SplashScreen(SGF::States::StateStack& stack, SGF::States::Context context) :
	AbstractState(stack, context)
{

}


SplashScreen::~SplashScreen()
{

}


bool SplashScreen::HandleEvent(SDL_Event& event)
{
	return true;
}


bool SplashScreen::Update(double deltaTime)
{
	return true;
}


void SplashScreen::Render()
{
	SDL_Renderer* renderer = GetContext().renderer;
	SGF::FontManager* fonts = GetContext().fontAssets;

	SGF::Assets::Font& font = fonts->Get("ROBOTO_REGULAR_10");

	SDL_Surface* textSurface = TTF_RenderText_Solid(font.GetPointer(), "Sandbox", { 255, 255, 255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { (1024 - 100) / 2, (768 - 20) / 2, 100, 20 };
	
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}