#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::EntitySystem
{
	class SGF_API Physics
	{
	public:
		typedef std::unique_ptr<Physics> Ptr;

		Physics(std::vector<AbstractEntityPtr>& entities);
		~Physics();

		void HandleCollisions();

	private:
		std::vector<Collision>::iterator _FindCollision(const AbstractEntity& entityA, const AbstractEntity& entityB);
		bool _CheckCollision(const AbstractEntity& entityA, const AbstractEntity& entityB) const;

	private:
		std::vector<AbstractEntityPtr>* m_Entities;
		std::vector<Collision> m_Collisions;
	};
}