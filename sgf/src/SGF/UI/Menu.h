#pragma once

#include "SGF/api.h"

#include "UIComponent.h"
#include "Structures.h"

namespace SGF::UI
{
	class SGF_API Menu : public UIComponent
	{
	public:
		Menu(const ComponentProperties* properties);
		~Menu();

		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;

		virtual void SetAnchorToCanvas(Canvas& canvas, Anchor anchor) override;

		virtual void SetPosition(int x, int y) override;
		virtual void SetPosition(Vector2i position) override;

		SDL_Color GetColor() const;
		void SetColor(SDL_Color color);

		SDL_Color GetHighlightColor() const;
		void SetHighlightColor(SDL_Color color);

		SDL_Color GetPressedColor() const;
		void SetPressedColor(SDL_Color color);

		void HandleEvent(SDL_Event& event);
		void Update(double deltaTime);
		void Render(SDL_Renderer* renderer);

	private:
		void _UpdateButtonsPosition();
		void _UpdateButtonsState();

	private:
		std::vector<ButtonPtr> m_Buttons;
		std::map<ButtonState, SDL_Color> m_StateColors;

		int m_SelectedItem;
		int m_Spacing;
	};
}