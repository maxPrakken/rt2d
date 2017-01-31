/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file entitymain.h
*
* @brief parent of everything that needs collision.
*/

#ifndef ENTITYMAIN_H
#define ENTITYMAIN_H

#include <rt2d/entity.h>

/// @brief the EntityMain class is the Entity implementation.
class EntityMain : public Entity
{
public:
	/// @brief constructor.
	EntityMain();

	/// @brief deconstructor.
	virtual ~EntityMain();

	/// @brief basic collision between player and other entity.
	bool isCollidingWith(Entity* other);

	

	

private:
};

#endif