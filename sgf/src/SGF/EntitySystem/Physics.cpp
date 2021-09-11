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
	for (auto& entityA : *m_Entities)
	{	
		for (auto& entityB : *m_Entities)
		{
			if (entityA.get() == entityB.get())
				break;

			auto iterator = _FindCollision(*entityA, *entityB);
			bool collided = _CheckCollision(*entityA, *entityB);

			if (collided && iterator == m_Collisions.end())
			{
				m_Collisions.push_back({ entityA.get(), entityB.get() });

				_HandleBasicCollision(*entityA, *entityB);
				_HandleBasicCollision(*entityB, *entityA);
				entityA->OnCollisionEnter(*entityB);
				entityB->OnCollisionEnter(*entityA);
			}
			else if (collided && iterator != m_Collisions.end())
			{
				_HandleBasicCollision(*entityA, *entityB);
				_HandleBasicCollision(*entityB, *entityA);
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
		ColliderBox colliderEntityA = entityA.GetCollider()->GetColliderBox();
		ColliderBox colliderEntityB = entityB.GetCollider()->GetColliderBox();

		if (dynamic_cast<const Mob*>(&entityA) != nullptr)
		{
			const Mob* mobEntity = static_cast<const Mob*>(&entityA);
			
			Vector2f size = mobEntity->GetSize();
			Vector2f position = mobEntity->GetPosition();
			Vector2f velocity = mobEntity->GetVelocity();

			colliderEntityA = ColliderBox(position.x + velocity.x, position.y + velocity.y, size.x, size.y);
		}

		SDL_Rect rectEntityA = colliderEntityA.ToRect();
		SDL_Rect rectEntityB = colliderEntityB.ToRect();

		result = SDL_HasIntersection(&rectEntityA, &rectEntityB) == SDL_TRUE;
	}

	return result;
}


void Physics::_HandleBasicCollision(AbstractEntity& entityA, AbstractEntity& entityB) const
{
	if (dynamic_cast<Mob*>(&entityA) == nullptr)
		return;

	Mob* mobEntity = static_cast<Mob*>(&entityA);
	Vector2f velocity = mobEntity->GetVelocity();

	ColliderBox mobCollider = mobEntity->GetCollider()->GetColliderBox();
	ColliderBox entityCollider = entityB.GetCollider()->GetColliderBox();

	if (mobCollider.top >= entityCollider.bottom || mobCollider.bottom <= entityCollider.top)
	{
		velocity.y = 0;
	}

	if (mobCollider.left >= entityCollider.right || mobCollider.right <= entityCollider.left)
	{
		velocity.x = 0;
	}

	mobEntity->SetVelocity(velocity);
}