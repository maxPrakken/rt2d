#include "CoolGuy.h"

CoolGuy::CoolGuy() : Entity()
{
	this->addSprite("assets/player.tga");
}


CoolGuy::~CoolGuy()
{
}
void CoolGuy::update(float deltaTime)
{
	/*this->rotation += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation > TWO_PI) {
		this->rotation -= TWO_PI;
	}*/
}
