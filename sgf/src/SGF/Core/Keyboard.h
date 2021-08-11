#pragma once

#include "SGF/api.h"

#include "Structures.h"

namespace SGF::Core
{
	class SGF_API Keyboard
	{
	private:
		Keyboard() {}
		~Keyboard() {}

	public:
		static bool isKeyDown(SDL_Scancode scancode);
		static bool isKeyUp(SDL_Scancode scancode);

		static void Init();
		static void HandleRealtimeInput();

	private:
		static std::unordered_map<SDL_Scancode, KeyState> s_KeysState;
	};
}

#define KEYBOARD SGF::Core::Keyboard