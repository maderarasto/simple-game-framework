#pragma once

#include "SGF/api.h"
#include "Structures.h"
#include "AbstractEntity.h"

namespace SGF::EntitySystem
{
	class SGF_API Mob : public AbstractEntity
	{
	public:
		Mob(Vector2f position, Vector2f size, Assets::Image& image);
		virtual ~Mob();

		Vector2f GetVelocity() const;
		void SetVelocity(Vector2f move);

		void Update(double deltaTime) override;

	private:
		Vector2f m_Velocity;
	};
}