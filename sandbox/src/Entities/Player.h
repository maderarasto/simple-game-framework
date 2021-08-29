#pragma once

#include "SGF/EntitySystem/Mob.h"
#include "SGF/Core/Vector2.h"
#include "SGF/Assets/Asset.h"

namespace Entities
{
	class Player : public SGF::EntitySystem::Mob
	{
	public:
		typedef std::unique_ptr<Player> Ptr;

		Player(Vector2f position, Vector2f size, SGF::Assets::Image& image);
		~Player();

		virtual inline std::string GetCategory() const override { return "Player"; }

		virtual void OnCollision(SGF::EntitySystem::AbstractEntity& entity) override;

		virtual void Update(double deltaTime) override;
	};
}