#ifndef ENTITYMAIN_H
#define ENTITYMAIN_H

#include <rt2d/entity.h>

class EntityMain : public Entity
{
public:
	EntityMain();
	virtual ~EntityMain();
	bool isCollidingWith(Entity* other);
private:

};

#endif