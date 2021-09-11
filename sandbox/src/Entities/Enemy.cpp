#include "sgfpch.h"
#include "Enemy.h"

#include "SGF/Core/Logger.h"

using namespace Entities;


Enemy::Enemy(Vector2f position, Vector2f size, SGF::Assets::Image& image) :
	Mob(position, size, image)
{

}


Enemy::~Enemy()
{

}


void Enemy::OnCollision(SGF::EntitySystem::AbstractEntity& entity)
{
	AbstractEntity::OnCollision(entity);

	APP_LOG_ERROR("ENEMY COLLISION");
}


void Enemy::Update(double deltaTime)
{
	SetVelocity(Vector2f(0.f, 1.f));
	Mob::Update(deltaTime);
}