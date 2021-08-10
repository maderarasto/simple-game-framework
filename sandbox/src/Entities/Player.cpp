#include "sgfpch.h"
#include "Player.h"

using namespace Entities;


Player::Player(Vector2f position, Vector2f size, SGF::Assets::Image& image) :
	Mob(position, size, image)
{

}


Player::~Player()
{

}


void Player::Update(double deltaTime)
{
	Mob::Update(deltaTime);
}