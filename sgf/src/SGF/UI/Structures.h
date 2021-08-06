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
		class Button;
		class Canvas;

		enum class Alignment
		{
			None = 0,
			Start, Center, End
		};

		enum class ButtonState
		{
			Idle, Highlighted, Pressed, Active
		};

		struct Anchor
		{
			Anchor(Alignment horizontal, Alignment vertical, Vector2i indent=Vector2i())
			{
				this->horizontal = horizontal;
				this->vertical = vertical;
				this->indent = indent;
			}
			
			Alignment horizontal;
			Alignment vertical;
			Vector2i indent;
		};

		struct MenuItem
		{
			std::string text;
			std::function<void()> action;
		};

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
			SDL_Color color = { 0, 0, 0 };
			std::string text;
		};

		struct ButtonProperties : public TextProperties
		{
			ButtonProperties() : TextProperties() {}

			SDL_Color highlightColor = { 255, 0, 0 };
			SDL_Color pressedColor = { 0, 0, 255 };
			std::function<void()> onClick;
		};

		struct MenuProperties : public ComponentProperties
		{
			MenuProperties() : ComponentProperties() {}

			Assets::Font* font;
			SDL_Color color = { 0, 0, 0 };
			SDL_Color highlightColor = { 255, 0, 0 };
			SDL_Color pressedColor = { 0, 0, 255 };
			std::vector<MenuItem> items;
			int spacing = 10;
		};

		typedef std::unique_ptr<UIComponent> UIComponentPtr;
		typedef std::unique_ptr<Text> TextPtr;
		typedef std::unique_ptr<Button> ButtonPtr;
		
		
		typedef std::function<void()> ButtonAction;
	}
}

typedef SGF::UI::Alignment SGF_Alignment;

#define NO_ANCHOR { Alignment::None, Alignment::None }