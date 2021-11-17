#pragma once

#include "SGF/api.h"

#include "UIComponent.h"
#include "Structures.h"

namespace SGF::UI
{
	class SGF_API Image : public UIComponent
	{
	public:
		Image(const ComponentProperties* properties);
		virtual ~Image();

		Assets::Image& GetSourceImage() const;
		void SetSourceImage(Assets::Image& image);

		void Render(SDL_Renderer* renderer);

	private:
		Assets::Image* m_SourceImage;
	};
}