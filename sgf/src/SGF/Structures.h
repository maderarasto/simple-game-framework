#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <memory>
#include <string>

namespace SGF
{
	namespace Assets {
		class Image;
		class Font;

		template<class Resource>
		class AssetManager;
	}

	namespace States {
		class StateStack;
	}
	
	struct SDL_Disposer
	{
		void operator()(SDL_Window* window) { SDL_DestroyWindow(window); }
		void operator()(SDL_Renderer* renderer) { SDL_DestroyRenderer(renderer); }
		void operator()(SDL_Surface* surface) { SDL_FreeSurface(surface); }
		void operator()(SDL_Texture* texture) { SDL_DestroyTexture(texture); }
		void operator()(TTF_Font* font) { TTF_CloseFont(font); }
	};

	struct AppConfig
	{
		std::string title;
		Uint32 resolution_width;
		Uint32 resolution_height;
	};

	typedef Assets::AssetManager<Assets::Image> ImageManager;
	typedef Assets::AssetManager<Assets::Font> FontManager;

	typedef std::unique_ptr<SDL_Window, SDL_Disposer> SDL_WindowPtr;
	typedef std::unique_ptr<SDL_Renderer, SDL_Disposer> SDL_RendererPtr;
	typedef std::unique_ptr<SDL_Surface, SDL_Disposer> SDL_SurfacePtr;
	typedef std::unique_ptr<SDL_Texture, SDL_Disposer> SDL_TexturePtr;
	typedef std::unique_ptr<TTF_Font, SDL_Disposer> TTF_FontPtr;

	typedef std::unique_ptr<ImageManager> ImageManagerPtr;
	typedef std::unique_ptr<FontManager> FontManagerPtr;
	typedef std::unique_ptr<States::StateStack> StateStackPtr;
}