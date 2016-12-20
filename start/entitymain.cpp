#include "entitymain.h" 

EntityMain::EntityMain() : Entity() {

}

EntityMain::~EntityMain() {

}



bool EntityMain::isCollidingWith(Entity* other) {
	if ((abs(this->position.x - other->position.x) * 2.0f < (sprite()->size.x * scale.x + other->sprite()->size.x * other->scale.x)) &&
		(abs(this->position.y - other->position.y) * 2.0f < (sprite()->size.y * scale.y + other->sprite()->size.y * other->scale.x)))
	{
		return true;
	}
	return false;
}