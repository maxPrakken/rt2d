#include "CoolGuy.h"

CoolGuy::CoolGuy() : Entity()
{
	addSpriteSheet("assets/player_idle_v2.tga", 2, 2);;
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
