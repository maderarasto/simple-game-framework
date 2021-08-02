#pragma once

#include "SGF/api.h"

#include "UIComponent.h"
#include "Structures.h"

namespace SGF::UI
{
	class SGF_API Button : public UIComponent
	{
	public:
		Button(const ComponentProperties* properties);
		~Button();

		void SetAnchorToCanvas(Canvas& canvas, Anchor anchor) override;

		void SetPosition(Vector2i position) override;
		void SetPosition(int x, int y) override;

		SDL_Color GetColor() const;
		void SetColor(SDL_Color color);

		SDL_Color GetHighlightedColor() const;
		void SetHighlightedColor(SDL_Color color);

		SDL_Color GetPressedColor() const;
		void SetPressedColor(SDL_Color color);

		std::string GetText() const;
		void SetText(std::string text);

		void SetOnClick(ButtonAction onClick);

		void HandleEvent(SDL_Event& event);
		void Update(double deltaTime);
		void Render(SDL_Renderer* renderer) override;

		bool _ResolveClick(SDL_MouseButtonEvent& event);
		bool _ResolveHighlight();

	private:
		TextPtr m_Text;
		ButtonState m_State;
		ButtonAction m_OnClick;
		std::unordered_map<ButtonState, SDL_Color> m_StateColors;
	};
}