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
			Context(SDL_Renderer* renderer, ImageManager* images, FontManager* fonts, LayoutManager* layouts)
			{
				this->renderer = renderer;
				this->imageAssets = images;
				this->fontAssets = fonts;
				this->layoutAssets = layouts;
			}

			SDL_Renderer* renderer;
			ImageManager* imageAssets;
			FontManager* fontAssets;
			LayoutManager* layoutAssets;
		};

		typedef std::unique_ptr<AbstractState> AbstractStatePtr;
		typedef std::function<AbstractStatePtr()> StateFactory;
	}
}