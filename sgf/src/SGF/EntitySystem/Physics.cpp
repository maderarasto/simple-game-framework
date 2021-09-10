#include "sgfpch.h"
#include "Physics.h"

#include "AbstractEntity.h"
#include "Mob.h"

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
	for (auto& stateEntityA : m_EntitiesState)
	{
		AbstractEntity* entityA = stateEntityA.entity;
		
		for (auto& stateEntityB : m_EntitiesState)
		{
			AbstractEntity* entityB = stateEntityB.entity;

			if (entityA == entityB)
				break;

			auto iterator = _FindCollision(*entityA, *entityB);
			bool collided = _CheckCollision(*entityA, *entityB);

			if (collided && iterator == m_Collisions.end())
			{
				m_Collisions.push_back({ entityA, entityB });

				_HandleBasicCollision(stateEntityA, stateEntityB);
				entityA->OnCollisionEnter(*entityB);
				entityB->OnCollisionEnter(*entityA);
			}
			else if (collided && iterator != m_Collisions.end())
			{
				_HandleBasicCollision(stateEntityA, stateEntityB);
				entityA->OnCollision(*entityB);
				entityB->OnCollision(*entityA);
			}
			else if (!collided && iterator != m_Collisions.end())
			{
				m_Collisions.erase(iterator);

				entityA->OnCollisionExit(*entityB);
				entityB->OnCollisionExit(*entityA);
			}
		}
	}

	_UpdateState();
}


void Physics::_UpdateState()
{
	_DismissNonExistentEntities();

	for (auto& entity : *m_Entities)
	{
		const auto& it = std::find_if(m_EntitiesState.begin(), m_EntitiesState.end(), [&entity](const EntityState& state)
			{
				return state.entity == entity.get();
			}
		);

		if (it != m_EntitiesState.end())
		{
			it->oldPosition = entity->GetPosition();
		}
		else
		{
			m_EntitiesState.push_back({ entity.get(), entity->GetPosition() });
		}
	}
}


void Physics::_DismissNonExistentEntities()
{
	std::vector<std::vector<EntityState>::iterator> markedForDismiss;

	for (auto it = m_EntitiesState.begin(); it != m_EntitiesState.end(); ++it)
	{
		const auto& foundIt = std::find_if(m_Entities->begin(), m_Entities->end(), [&it](const AbstractEntityPtr& entity)
			{
				return entity.get() == it->entity;
			}
		);

		if (foundIt == m_Entities->end())
		{
			markedForDismiss.push_back(it);
		}
	}

	for (auto& stateIt : markedForDismiss)
	{
		m_EntitiesState.erase(stateIt);
	}

	markedForDismiss.clear();
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

		if (dynamic_cast<const Mob*>(&entityA) != nullptr)
		{
			//CORE_LOG_WARNING("EntityA: ({}, {}), ColliderA: ({}, {}), ColliderB: ({}, {})", entityA.GetPosition().x, entityA.GetPosition().y, colliderEntityA.x, colliderEntityA.y, colliderEntityB.x + colliderEntityB.w, colliderEntityB.y + colliderEntityB.h);

			const Mob* mobEntity = static_cast<const Mob*>(&entityA);
			colliderEntityA = {
				colliderEntityA.x + static_cast<int>(mobEntity->GetVelocity().x),
				colliderEntityA.y + static_cast<int>(mobEntity->GetVelocity().y),
				colliderEntityA.w,
				colliderEntityB.h
			};
		}

		result = SDL_HasIntersection(&colliderEntityA, &colliderEntityB) == SDL_TRUE;
	}

	return result;
}


void Physics::_HandleBasicCollision(const EntityState& stateEntityA, const EntityState& stateEntityB) const
{
	if (dynamic_cast<Mob*>(stateEntityA.entity) == nullptr)
		return;

	Mob* mobEntity = static_cast<Mob*>(stateEntityA.entity);

	Vector2f position = mobEntity->GetPosition();
	Vector2f velocity = mobEntity->GetVelocity();

	if (stateEntityA.entity->GetPosition().y > (stateEntityB.entity->GetPosition().y + stateEntityB.entity->GetSize().y - 1) || 
		(stateEntityA.entity->GetPosition().y + stateEntityA.entity->GetSize().y - 1) < stateEntityB.entity->GetPosition().y)
	{
		velocity.y = 0;
	}

	if (stateEntityA.entity->GetPosition().x > (stateEntityB.entity->GetPosition().x + stateEntityB.entity->GetSize().x - 1) ||
		(stateEntityA.entity->GetPosition().x + stateEntityA.entity->GetSize().x - 1) < stateEntityB.entity->GetPosition().x)
	{
		velocity.x = 0;
	}

	mobEntity->SetVelocity(velocity);
}