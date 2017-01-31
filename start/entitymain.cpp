#include "entitymain.h" 

EntityMain::EntityMain() : Entity() {

}

EntityMain::~EntityMain() {

}

bool EntityMain::isCollidingWith(Entity* other) {
	float dx = this->position.x - other->position.x;
	float dy = this->position.y - other->position.y;

	if ((abs(dx) * 2.0f < (sprite()->size.x  + other->sprite()->size.x)) &&
		(abs(dy) * 2.0f < (sprite()->size.y  + other->sprite()->size.y )))
	{
		//std::cout << dx << "," << dy << std::endl;
		return true;
	}
	return false;
}



