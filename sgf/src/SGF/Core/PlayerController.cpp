#include "sgfpch.h"
#include "PlayerController.h"

#include "Logger.h"
#include "Keyboard.h"
#include "CommandQueue.h"

#include "SGF/EntitySystem/Mob.h"

using namespace SGF::Core;


PlayerController::PlayerController(Keyboard& keyboard) :
	m_Keyboard(&keyboard)
{
	_InitKeyBindings();
	_InitActionBindings();
}


PlayerController::~PlayerController()
{

}


void PlayerController::HandleRealtimeInput(CommandQueue& commands)
{	
	for (auto it = m_KeyBindings.begin(); it != m_KeyBindings.end(); ++it)
	{
	
		if (m_Keyboard->isKeyDown(it->first))
		{
			Command command = m_ActionBindings[it->second];
			commands.Push(command);
		}
	}
}


PlayerController::PlayerMover::PlayerMover(float velocityX, float velocityY) :
	velocity(velocityX, velocityY)
{
}


void PlayerController::PlayerMover::operator()(EntitySystem::Mob& mob) const
{
	Vector2f current = mob.GetVelocity();
	Vector2f result = current + velocity;

	mob.SetVelocity(result);
}


void PlayerController::_InitKeyBindings()
{
	m_KeyBindings[SDL_SCANCODE_W] = PlayerAction::MoveUp;
	m_KeyBindings[SDL_SCANCODE_S] = PlayerAction::MoveDown;
	m_KeyBindings[SDL_SCANCODE_A] = PlayerAction::MoveLeft;
	m_KeyBindings[SDL_SCANCODE_D] = PlayerAction::MoveRight;
}


void PlayerController::_InitActionBindings()
{
	m_ActionBindings[PlayerAction::MoveUp].action = derivedAction<EntitySystem::Mob>(PlayerMover(0.f, -1.f));
	m_ActionBindings[PlayerAction::MoveDown].action = derivedAction<EntitySystem::Mob>(PlayerMover(0.f, 1.f));
	m_ActionBindings[PlayerAction::MoveLeft].action = derivedAction<EntitySystem::Mob>(PlayerMover(-1.f, 0.f));
	m_ActionBindings[PlayerAction::MoveRight].action = derivedAction<EntitySystem::Mob>(PlayerMover(1.f, 0.f));

	for (auto& it : m_ActionBindings)
	{
		it.second.category = "Player";
	}
}