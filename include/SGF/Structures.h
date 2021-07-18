#pragma once

#include <SDL.h>
#include <memory>

namespace SGF
{
	struct SDL_Disposer
	{
		void operator()(SDL_Window* window) { SDL_DestroyWindow(window); }
		void operator()(SDL_Renderer* renderer) { SDL_DestroyRenderer(renderer); }
	};

	typedef std::unique_ptr<SDL_Window, SDL_Disposer> SDL_WindowPtr;
	typedef std::unique_ptr<SDL_Renderer, SDL_Disposer> SDL_RendererPtr;
}