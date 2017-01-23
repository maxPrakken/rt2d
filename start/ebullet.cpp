#include "ebullet.h" 
 
Ebullet::Ebullet(){
	this->addSprite("assets/bullet.tga");

	velocity = Vector2(0, 0);

	gravity = 100;
}
 
Ebullet::~Ebullet(){

}

void Ebullet::update(float deltatime) {
	//bullet gravity
	position += velocity * deltatime;
	velocity.y += gravity * deltatime;
}