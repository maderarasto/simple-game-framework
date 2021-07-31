#pragma once

#include "SGF/Core/Vector2.h"

namespace SGF
{
	namespace EntitySystem
	{
		class AbstractEntity;
		class Mob;
		class Sprite;

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