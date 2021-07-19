#pragma once

#include "SGF/api.h"
#include <SDL.h>

namespace SGF::Core
{
	class SGF_API Clock
	{
	public:
		Clock()
		{
			m_StartTime = SDL_GetTicks();
		}

		double Reset()
		{
			Uint32 lastTime = SDL_GetTicks();
			Uint32 elapsedTime = lastTime - m_StartTime;

			m_StartTime = lastTime;
			
			return elapsedTime;
		}

	public:
		static const double OneSecond;

	private:
		Uint32 m_StartTime;
	};

	const double Clock::OneSecond = 1000.0;
}