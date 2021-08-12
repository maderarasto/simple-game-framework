#include "sgfpch.h"
#include "Keyboard.h"

#include "Logger.h"

using namespace SGF::Core;

std::unordered_map<SDL_Scancode, Key> Keyboard::s_KeysState;

bool Keyboard::IsKeyDown(SDL_Scancode scancode)
{
	return s_KeysState.at(scancode).state == KeyState::KeyDown;
}


bool Keyboard::IsKeyUp(SDL_Scancode scancode)
{
	return s_KeysState.at(scancode).state == KeyState::KeyUp;
}


bool Keyboard::IsKeyPressed(SDL_Scancode scancode)
{
	return s_KeysState.at(scancode).pressed;
}


void Keyboard::Init()
{
	for (Uint16 scancode = 0; scancode < SDL_NUM_SCANCODES; scancode++)
	{
		s_KeysState[(SDL_Scancode)scancode].state = KeyState::KeyUp;
	}
}


void Keyboard::HandleRealtimeInput()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	for (Uint16 i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		auto scancode = static_cast<SDL_Scancode>(i);
		
		s_KeysState[scancode].pressed = !IsKeyDown(scancode) && keyboardState[i] > 0;
		s_KeysState[scancode].state = keyboardState[i] > 0 ? KeyState::KeyDown : KeyState::KeyUp;
	}
}