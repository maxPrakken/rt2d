/**
 * Copyright 2015 Your Name <maxprakken3@hotmail.nl>
 *
 * @file myentity.h
 *
 * @brief basic entity that has no collision.
 */

#ifndef MYENTITY_H
#define MYENTITY_H

#include <rt2d/entity.h>

/// @brief The MyEntity class is the Entity implementation.
class MyEntity : public Entity
{
public:
	/// @brief Constructor
	MyEntity();
	/// @brief Destructor
	virtual ~MyEntity();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
