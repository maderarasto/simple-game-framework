#include "sgfpch.h"
#include "Physics.h"

#include "AbstractEntity.h"

#include "SGF/Core/Logger.h"

using namespace SGF::EntitySystem;


Physics::Physics(std::vector<AbstractEntityPtr>& entities) :
	m_Entities(&entities)
{

}


Physics::~Physics()
{

}


void Physics::HandleCollisions()
{
	for (auto& entity : *m_Entities)
	{	
		for (auto& otherEntity : *m_Entities)
		{
			if (entity.get() == otherEntity.get())
				break;

			auto iterator = _FindCollision(*entity, *otherEntity);
			bool collided = _CheckCollision(*entity, *otherEntity);

			if (collided && iterator == m_Collisions.end())
			{
				m_Collisions.push_back({ entity.get(), otherEntity.get() });
				entity->OnCollisionEnter(*otherEntity);
			}
			else if (collided && iterator != m_Collisions.end())
			{
				entity->OnCollision(*otherEntity);
			}
			else if (!collided && iterator != m_Collisions.end())
			{
				m_Collisions.erase(iterator);
				entity->OnCollisionExit(*otherEntity);
			}
		}
	}
}


std::vector<Collision>::iterator Physics::_FindCollision(const AbstractEntity& entityA, const AbstractEntity& entityB)
{
	return std::find_if(m_Collisions.begin(), m_Collisions.end(), [&entityA, &entityB](const Collision& collision)
		{
			return collision.source == &entityA && collision.target == &entityB;
		}
	);
}


bool Physics::_CheckCollision(const AbstractEntity& entityA, const AbstractEntity& entityB) const
{
	bool result = entityA.GetCollider() != NULL && entityB.GetCollider() != NULL;

	if (result)
	{
		SDL_Rect colliderEntityA = entityA.GetCollider()->GetBounds();
		SDL_Rect colliderEntityB = entityB.GetCollider()->GetBounds();

		result = SDL_HasIntersection(&colliderEntityA, &colliderEntityB) == SDL_TRUE;
	}

	return result;
}