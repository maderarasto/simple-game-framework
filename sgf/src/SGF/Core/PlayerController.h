#pragma once

#include "SGF/api.h"

#include "Structures.h"

namespace SGF::Core
{
	class SGF_API PlayerController
	{
	public:
		typedef std::unique_ptr<PlayerController> Ptr;

		PlayerController();
		~PlayerController();

		void HandleRealtimeInput(CommandQueue& commands);

	private:
		void _InitKeyBindings();
		void _InitActionBindings();

	private:
		struct PlayerMover
		{
			PlayerMover(float velocityX, float velocityY);
			void operator()(EntitySystem::Mob& mob) const;

			Vector2f velocity;
		};

	private:
		std::unordered_map<SDL_Scancode, PlayerAction> m_KeyBindings;
		std::unordered_map<PlayerAction, Command> m_ActionBindings;
	};
}