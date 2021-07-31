#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::EntitySystem
{
	class SGF_API Sprite
	{
	public:
		Sprite(AbstractEntity& entity, Assets::Image& image);
		~Sprite();

		void SetImage(Assets::Image& image);
		void UpdateBorder();

		void Render(SDL_Renderer* renderer);

	private:
		AbstractEntity* m_Entity;
		Assets::Image* m_Image;

		SDL_Rect m_Border;
	};
}