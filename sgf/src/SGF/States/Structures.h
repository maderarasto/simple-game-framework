#pragma once

#include "SGF/api.h"
#include "SGF/Structures.h"

namespace SGF
{	
	namespace UI
	{
		class Canvas;
	}

	namespace States
	{
		class StateStack;
		class AbstractState;

		struct SGF_API Context
		{
			Context(SDL_Renderer* renderer, Core::Keyboard* keyboard, ImageManager* images, FontManager* fonts)
			{
				this->renderer = renderer;
				this->keyboard = keyboard;
				this->imageAssets = images;
				this->fontAssets = fonts;
			}

			SDL_Renderer* renderer;
			Core::Keyboard* keyboard;
			ImageManager* imageAssets;
			FontManager* fontAssets;
		};

		typedef std::unique_ptr<AbstractState> AbstractStatePtr;
		typedef std::function<AbstractStatePtr()> StateFactory;
	}
}