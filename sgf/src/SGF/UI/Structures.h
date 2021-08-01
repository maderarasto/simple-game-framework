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

		typedef std::unique_ptr<UIComponent> UIComponentPtr;
		typedef std::unique_ptr<Text> TextPtr;
	}
}