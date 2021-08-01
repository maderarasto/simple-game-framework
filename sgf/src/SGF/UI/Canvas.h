#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::UI
{
	class SGF_API Canvas
	{
	public:
		Canvas(int width, int height);
		~Canvas();

		Canvas(const Canvas&) = delete;
		Canvas& operator=(const Canvas&) = delete;

		SDL_Color GetBackgroundColor() const;
		void SetBackgroundColor(SDL_Color color);

		template<typename Component>
		void AddComponent();
		void RemoveComponentAt(Uint32 index);

		void HandleEvent(SDL_Event& event);
		void Update(double deltaTime);
		void Render(SDL_Renderer* renderer);

	private:
		int m_Width, m_Height;
		SDL_Rect m_Border;
		SDL_Color m_BackgroundColor;


		std::vector<UIComponentPtr> m_Components;
	};

	template<typename Component>
	void Canvas::AddComponent()
	{
	}
}