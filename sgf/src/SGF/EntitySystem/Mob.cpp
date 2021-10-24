#include "sgfpch.h"
#include "Mob.h"

#include "SGF/Assets/Asset.h"
#include "SGF/Core/Logger.h"

using namespace SGF::EntitySystem;


Mob::Mob(Vector2f position, Vector2f size, Assets::Image& image) :
	AbstractEntity(position, size, image),
	m_Velocity(0.f, 0.f)
{
}


Mob::~Mob()
{

}


Vector2f Mob::GetVelocity() const
{
	return m_Velocity;
}


void Mob::SetVelocity(Vector2f velocity)
{
	m_Velocity = velocity;
}


void Mob::Update(double deltaTime)
{
}


void Mob::FixedUpdate(double deltaTime)
{
	Vector2f position = GetPosition() + m_Velocity;

	SetPosition(position);

	m_Velocity = Vector2f(0.f, 0.f);
}