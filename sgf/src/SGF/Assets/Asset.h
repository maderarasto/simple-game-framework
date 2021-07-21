#pragma once

#include "SGF/Structures.h"

namespace SGF::Assets
{
	class IAsset
	{
		virtual bool LoadFromFile(const std::string& fileName) = 0;
	};

	class Image : IAsset
	{
	public:
		Image() {};

		inline SDL_Surface* GetPointer() { return m_Surface.get(); }

		virtual bool LoadFromFile(const std::string& fileName)
		{
			SDL_Surface* surface = IMG_Load(fileName.c_str());

			if (!surface)
				return false;

			m_Surface = SDL_SurfacePtr(std::move(surface));

			return true;
		}

	private:
		SDL_SurfacePtr m_Surface;
	};

	class Font : public IAsset
	{
	public:
		Font(Uint32 size = 12) : m_Size(size) {}

		inline TTF_Font* GetPointer() { return m_Font.get(); }

		virtual bool LoadFromFile(const std::string& fileName)
		{
			TTF_Font* font = TTF_OpenFont(fileName.c_str(), m_Size);

			if (!font)
				return false;

			m_Font = TTF_FontPtr(std::move(font));

			return true;
		}

	private:
		Uint32 m_Size;
		TTF_FontPtr m_Font;
	};
}