#include "CoolGuy.h"

CoolGuy::CoolGuy() : Entity()
{
	//addSprite("assets/player.tga");
	addSpriteSheet("assets/player_animations_full.tga", 2, 6);

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
