#include "enemies.h" 
 
Enemies::Enemies() : EntityMain()
{
	addSpriteSheet("assets/enemy_animations_full_V1.tga", 2, 6);

	velocity = Vector2(0, 0);
	gravity = 700;
}
 
Enemies::~Enemies()
{

}

bool Enemies::detectionZone(Entity* other, int zonesize) {
	if ((abs(this->position.x - other->position.x) * 2.0f < (sprite()->size.x * zonesize + other->sprite()->size.x)) &&
		(abs(this->position.y - other->position.y) * 2.0f < (sprite()->size.y * zonesize + other->sprite()->size.y)))
	{
		return true;
	}
	return false;
}

void Enemies::update(float deltatime)
{
	//enemy gravity
	position += velocity * deltatime;
	velocity.y += gravity * deltatime;
}