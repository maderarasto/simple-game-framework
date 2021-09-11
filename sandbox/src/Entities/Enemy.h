#pragma once

#include "SGF/EntitySystem/Mob.h"

namespace Entities
{
	class Enemy : public SGF::EntitySystem::Mob
	{
	public:
		Enemy(Vector2f position, Vector2f size, SGF::Assets::Image& image);
		virtual ~Enemy();

		virtual inline std::string GetCategory() const override { return "Enemy"; }

		virtual void OnCollision(SGF::EntitySystem::AbstractEntity& entity) override;

		virtual void Update(double deltaTime) override;
	};
}