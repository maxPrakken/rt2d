#include "enemies.h" 
 
Enemy::Enemy() : EntityMain()
{
	addSpriteSheet("assets/enemy_animations_full_V2.tga", 2, 6);

	velocity = Vector2(0, 0);
	gravity = 700;
}
 
Enemy::~Enemy()
{

}

bool Enemy::detectionZone(Entity* other, int zonesize) {
	if ((abs(this->position.x - other->position.x) * 2.0f < (sprite()->size.x * zonesize + other->sprite()->size.x)) &&
		(abs(this->position.y - other->position.y) * 2.0f < (sprite()->size.y * zonesize + other->sprite()->size.y)))
	{
		return true;
	}
	return false;
}

void Enemy::update(float deltatime)
{
	//enemy gravity
	position += velocity * deltatime;
	velocity.y += gravity * deltatime;
}