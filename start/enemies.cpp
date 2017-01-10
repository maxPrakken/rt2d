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

void Enemies::update(float deltatime)
{
	//enemy gravity
	position += velocity * deltatime;
	velocity.y += gravity * deltatime;
}