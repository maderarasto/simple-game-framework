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

		inline virtual std::string GetCategory() const override { return "Mob"; }

		Vector2f GetVelocity() const;
		void SetVelocity(Vector2f move);

		virtual void Update(double deltaTime) override;
		void FixedUpdate(double deltaTime);

	private:
		Vector2f m_Velocity;
	};
}