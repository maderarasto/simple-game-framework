#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::UI
{
	class SGF_API UIComponent
	{
	public:
		UIComponent(const ComponentProperties* properties);
		virtual ~UIComponent();

		inline SDL_Rect GetBorder() const { return m_Border; };

		virtual void SetAnchorToCanvas(Canvas& canvas, Anchor anchor);

		Vector2i GetPosition() const;
		virtual void SetPosition(int x, int y);
		virtual void SetPosition(Vector2i position);

		Vector2i GetSize() const;
		virtual void SetSize(int w, int h);
		virtual void SetSize(Vector2i size);

		virtual void Render(SDL_Renderer* renderer) = 0;

	private:
		void _ResolvePositionX();
		void _ResolvePositionY();
		void _UpdateBorder();

	private:
		Vector2i m_Position;
		Vector2i m_Size;
		
		Canvas* m_Canvas;
		SDL_Rect m_Border;
		Anchor m_Anchor;
	};
}