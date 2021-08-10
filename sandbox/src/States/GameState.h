#pragma once

#include "SGF/States/AbstractState.h"
#include "SGF/Core/CommandQueue.h"
#include "SGF/Core/PlayerController.h"
#include "SGF/UI/Text.h"
#include "SGF/UI/Button.h"
#include "SGF/UI/Menu.h"

#include "../Entities/Player.h"

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

	private:
		SGF::Core::CommandQueue::Ptr m_CommandQueue;
		SGF::Core::PlayerController::Ptr m_PlayerController;

		Entities::Player::Ptr m_Player;
	};
}