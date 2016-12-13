#include "CoolGuy.h"

CoolGuy::CoolGuy() : Entity()
{
	this->addSprite("assets/player.tga");
	velocity = Vector2(0, 0);

	gravity = 700;
}


CoolGuy::~CoolGuy()
{
}
void CoolGuy::update(float deltaTime)
{
	//player gravity
	position += velocity * deltaTime;
	velocity.y += gravity * deltaTime;
}
