#pragma once

#include "api.h"
#include "Structures.h"

#include <memory>

namespace SGF
{
	class SGF_API Application
	{
	public:
		Application();

		void SetFrameRate(double frameRate);

		void Run();

	private:
		void _HandleEvents();
		void _Update(double deltaTime);
		void _Render();


	public:

		
	private:
		SDL_WindowPtr m_Window;
		SDL_RendererPtr m_Renderer;

		bool m_Running;
		double m_TimePerUpdate;
	};
}