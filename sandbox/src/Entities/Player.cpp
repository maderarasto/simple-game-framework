#include "sgfpch.h"
#include "Player.h"

#include "SGF/Core/Keyboard.h"
#include "SGF/Core/Logger.h"

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

	if (KEYBOARD::IsKeyPressed(SDL_SCANCODE_SPACE))
	{
		APP_LOG_INFO("FRANKY FIIIRE");
	}
}