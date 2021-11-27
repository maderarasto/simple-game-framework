#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::Assets
{
	class Layout;
}

namespace SGF::UI
{
	class SGF_API Canvas
	{
	public:
		Canvas(int width, int height);
		~Canvas();

		Canvas(const Canvas&) = delete;
		Canvas& operator=(const Canvas&) = delete;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		SDL_Color GetBackgroundColor() const;
		void SetBackgroundColor(SDL_Color color);

		void AddComponentsFromLayout(const Assets::Layout& layout);

		template<typename Component>
		void AddComponent(ComponentProperties* properties, Anchor anchor=NO_ANCHOR);
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
	void Canvas::AddComponent(ComponentProperties* properties, Anchor anchor)
	{
		std::unique_ptr<Component> component = std::make_unique<Component>(properties);

		if (anchor.horizontal != Alignment::None || anchor.vertical != Alignment::None)
			component->SetAnchorToCanvas(*this, anchor);

		m_Components.push_back(std::move(component));
	}
}