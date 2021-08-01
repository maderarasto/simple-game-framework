#pragma once

#include "SGF/Core/Vector2.h"

namespace SGF
{
	namespace Assets
	{
		class Font;
	}

	namespace UI
	{
		class UIComponent;
		class Text;

		struct ComponentProperties
		{	
			ComponentProperties() {};
			
			Vector2i position;
			Vector2i size;
		};

		struct TextProperties : public ComponentProperties
		{
			TextProperties() : ComponentProperties() {};
			
			Assets::Font* font;
			SDL_Color color;
			std::string text;
		};

		typedef std::unique_ptr<UIComponent> UIComponentPtr;
		typedef std::unique_ptr<Text> TextPtr;
	}
}