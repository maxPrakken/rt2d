#include "bullet.h" 
 
Bullet::Bullet() : EntityMain(){
	this->addSprite("assets/bullet.tga");

	velocity = Vector2(0, 0);

	gravity = 150;
}
 
Bullet::~Bullet(){

}

void Bullet::update(float deltatime) {
	//bullet gravity
	position += velocity * deltatime;
	velocity.y += gravity * deltatime;
}