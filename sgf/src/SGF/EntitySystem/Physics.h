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
		inline static bool _InRange(float number, float min, float max) { return number >= min && number <= max; }
		
		void _DismissNonExistentEntities();
		void _UpdateState();
		std::vector<Collision>::iterator _FindCollision(const AbstractEntity& entityA, const AbstractEntity& entityB);
		bool _CheckCollision(const AbstractEntity& entityA, const AbstractEntity& entityB) const;
		void _HandleBasicCollision(const EntityState& stateEntityA, const EntityState& stateEntityB) const;

	private:
		std::vector<AbstractEntityPtr>* m_Entities;
		std::vector<EntityState> m_EntitiesState;
		std::vector<Collision> m_Collisions;
	};
}