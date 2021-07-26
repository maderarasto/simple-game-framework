#pragma once

#include "SGF/Structures.h"

namespace SGF::States
{	
	class StateStack;
	class AbstractState;
	
	struct Context
	{
		SDL_Renderer* renderer;
		ImageManager* imageAssets;
		FontManager* fontAssets;
	};

	typedef std::unique_ptr<AbstractState> AbstractStatePtr;
	typedef std::function<AbstractStatePtr()> StateFactory;
}