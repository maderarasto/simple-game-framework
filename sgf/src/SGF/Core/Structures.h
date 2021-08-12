#pragma once

#include <string>
#include <stdexcept>
#include <functional>

#include "Vector2.h"

namespace SGF
{
	namespace EntitySystem
	{
		class AbstractEntity;
		class Mob;
	}

	namespace Core
	{
		class Keyboard;
		class CommandQueue;

		enum class PlayerAction
		{
			MoveUp,
			MoveDown,
			MoveLeft,
			MoveRight
		};

		enum class KeyState
		{
			KeyUp,
			KeyDown
		};

		struct Key
		{
			KeyState state = KeyState::KeyUp;
			bool pressed = false;
		};

		struct Command
		{
			typedef std::function<void(EntitySystem::AbstractEntity& mob)> Action;

			std::string category;
			Action action;
		};

		template<typename Entity, typename Callback>
		Command::Action derivedAction(Callback callback)
		{
			return [=](EntitySystem::AbstractEntity& entity)
			{
				if (dynamic_cast<Entity*>(&entity) == NULL)
					throw std::runtime_error("Error occured while casting to derived entity!");

				callback(static_cast<Entity&>(entity));
			};
		}
	}
}