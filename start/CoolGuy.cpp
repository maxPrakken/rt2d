#include "CoolGuy.h"

CoolGuy::CoolGuy() : EntityMain()
{
	addSpriteSheet("assets/player_animations_full_v2.tga", 2, 6);

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
