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
		static bool IsKeyDown(SDL_Scancode scancode);
		static bool IsKeyUp(SDL_Scancode scancode);
		static bool IsKeyPressed(SDL_Scancode scancode);

		static void Init();
		static void HandleRealtimeInput();

	private:
		static std::unordered_map<SDL_Scancode, Key> s_KeysState;
	};
}

#define KEYBOARD SGF::Core::Keyboard