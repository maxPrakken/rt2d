#include "entitymain.h" 
 
EntityMain::EntityMain() : Entity(){
 
}
 
EntityMain::~EntityMain(){

}

bool EntityMain::isCollidingWith(Entity* other) {
	float thisTop = -this->sprite()->size.y / 2.0f + this->position.y;
	float thisBottom = this->sprite()->size.y / 2.0f + this->position.y;
	float thisLeft = -this->sprite()->size.x / 2.0f + this->position.x;
	float thisRight = this->sprite()->size.x / 2.0f + this->position.x;

	float otherTop = -other->sprite()->size.y / 2.0f + other->position.y;
	float otherBottom = other->sprite()->size.y / 2.0f + other->position.y;
	float otherLeft = -other->sprite()->size.x / 2.0f + other->position.x;
	float otherRight = other->sprite()->size.x / 2.0f + other->position.x;

	if ((thisTop < otherBottom && thisTop > otherTop) &&
		(thisLeft < otherRight && thisLeft > otherLeft)) {
		return true;
	}

	if ((thisTop < otherBottom && thisTop > otherTop) &&
		(thisRight > otherLeft && thisRight < otherRight)) {
		return true;
	}


	///////////////////////	///////////////////////


	if ((thisBottom > otherTop && thisBottom < otherBottom) &&
		(thisLeft < otherRight && thisLeft > otherLeft)) {
		return true;
	}

	if ((thisBottom > otherTop && thisBottom < otherBottom) &&
		(thisRight > otherLeft && thisRight < otherRight)) {
		return true;
	}

	return false;
}