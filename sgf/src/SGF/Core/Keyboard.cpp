#include "sgfpch.h"
#include "Keyboard.h"

#include "Logger.h"

using namespace SGF::Core;

std::unordered_map<SDL_Scancode, KeyState> Keyboard::s_KeysState;

bool Keyboard::isKeyDown(SDL_Scancode scancode)
{
	return s_KeysState.at(scancode) == KeyState::KeyDown;
}


bool Keyboard::isKeyUp(SDL_Scancode scancode)
{
	return s_KeysState.at(scancode) == KeyState::KeyUp;
}


void Keyboard::Init()
{
	for (Uint16 scancode = 0; scancode < SDL_NUM_SCANCODES; scancode++)
	{
		s_KeysState[(SDL_Scancode)scancode] = KeyState::KeyUp;
	}
}


void Keyboard::HandleRealtimeInput()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	for (Uint16 i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		s_KeysState[(SDL_Scancode)i] = keyboardState[i] > 0 ? KeyState::KeyDown : KeyState::KeyUp;
	}
}