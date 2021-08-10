#include "sgfpch.h"
#include "Keyboard.h"

#include "Logger.h"

using namespace SGF::Core;


Keyboard::Keyboard()
{
	for (Uint16 scancode = 0; scancode < SDL_NUM_SCANCODES; scancode++)
	{
		m_KeysState[(SDL_Scancode) scancode] = KeyState::KeyUp;
	}
}


Keyboard::~Keyboard()
{

}


bool Keyboard::isKeyDown(SDL_Scancode scancode) const
{
	return m_KeysState.at(scancode) == KeyState::KeyDown;
}


bool Keyboard::isKeyUp(SDL_Scancode scancode) const
{
	return m_KeysState.at(scancode) == KeyState::KeyUp;
}


void Keyboard::HandleRealtimeInput()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	for (Uint16 i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_KeysState[(SDL_Scancode)i] = keyboardState[i] > 0 ? KeyState::KeyDown : KeyState::KeyUp;
	}
}