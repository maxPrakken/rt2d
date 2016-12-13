#include "bullet.h" 
 
Bullet::Bullet() : Entity(){
	this->addSprite("assets/bullet.tga");

	velocity = Vector2(0, 0);

	gravity = 100;
}
 
Bullet::~Bullet(){

}

void Bullet::update(float deltatime) {
	//bullet gravity
	position += velocity * deltatime;
	velocity.y += gravity * deltatime;
}