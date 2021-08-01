#pragma once

#include "SGF/api.h"
#include "UIComponent.h"
#include "Structures.h"

namespace SGF::UI
{
	class SGF_API Text : public UIComponent
	{
	public:
		Text(const ComponentProperties& props);
		~Text();

		Assets::Font& GetFont() const;
		void SetFont(Assets::Font& font);

		SDL_Color GetColor() const;
		void SetColor(SDL_Color color);

		std::string GetText() const;
		void SetText(std::string text);

		void Render(SDL_Renderer* renderer) override;

	private:
		void _ResolveTextSize();

	private:
		Assets::Font* m_Font;
		SDL_Color m_Color;
		std::string m_Text;
	};
}