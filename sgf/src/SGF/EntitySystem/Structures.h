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

		struct ColliderBox
		{
			ColliderBox()
			{
				top = 0;
				left = 0;
				bottom = 0;
				right = 0;
			}

			ColliderBox(int x, int y, int width, int height)
			{
				top = y;
				left = x;
				bottom = y + height - 1;
				right = x + width - 1;
			}

			SDL_Rect ToRect()
			{
				return {
					left, 
					top, 
					right - left + 1, 
					bottom - top + 1
				};
			}

			int top, bottom;
			int left, right;
		};

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
			
			ColliderBox GetColliderBox()
			{
				return ColliderBox(position.x, position.y, size.x, size.y);
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