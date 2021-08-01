#pragma once

#include "SGF/States/AbstractState.h"
#include "SGF/EntitySystem/Mob.h"
#include "SGF/UI/Text.h"

namespace States
{
	class GameState : public SGF::States::AbstractState
	{
	public:
		GameState(SGF::States::StateStack& stack, SGF::States::Context context);
		~GameState();

		bool HandleEvent(SDL_Event& event) override;
		bool Update(double deltaTime) override;
		void Render() override;
	};
}