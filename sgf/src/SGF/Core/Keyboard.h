#pragma once

#include "SGF/api.h"

#include "Structures.h"

namespace SGF::Core
{
	class SGF_API Keyboard
	{
	public:
		Keyboard();
		~Keyboard();

		bool isKeyDown(SDL_Scancode scancode) const;
		bool isKeyUp(SDL_Scancode scancode) const;

		void HandleRealtimeInput();

	private:
		std::unordered_map<SDL_Scancode, KeyState> m_KeysState;
	};
}