#pragma once

#include "SGF/Core/Vector2.h"
#include "SDL.h"

namespace SGF
{
	namespace EntitySystem
	{
		class AbstractEntity;
		class Mob;
		class Sprite;

		struct Collider
		{
			typedef std::unique_ptr<Collider> Ptr;
			
			Collider() :
				position(0.f, 0.f),
				size(0.f, 0.f)
			{

			}

			Collider(Vector2f position, Vector2f size) :
				position(position),
				size(size)
			{

			}
			
			SDL_Rect GetBounds() const
			{
				SDL_Rect bounds;

				bounds.x = static_cast<int>(position.x);
				bounds.y = static_cast<int>(position.y);
				bounds.w = static_cast<int>(size.x);
				bounds.h = static_cast<int>(size.y);

				return bounds;
			}

			Vector2f position;
			Vector2f size;
		};

		struct Collision
		{
			bool operator==(const Collision& other) const
			{
				return source == other.source && target == other.target;
			}

			AbstractEntity* source;
			AbstractEntity* target;
		};

		struct EntityState {
			AbstractEntity* entity;
			Vector2f oldPosition;
		};

		enum class CollisionSide
		{
			None = 0,
			Top, Right, Bottom, Left
		};

		typedef std::unique_ptr<AbstractEntity> AbstractEntityPtr;
		typedef std::unique_ptr<Mob> MobPtr;
		typedef std::unique_ptr<Sprite> SpritePtr;
	}
	
	namespace Assets
	{
		class Image;
		class Font;
	}
}