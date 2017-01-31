/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file enemies.h
*
* @brief entity enemies
*/

#pragma once
#include "entitymain.h"

class Enemy :
	public EntityMain
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void update(float deltatime);

	/// @brief speed of enemy in pixels per second.
	Vector2 velocity;

	/// @brief amound of gravity on enemy in pixels per second.
	int gravity;

	/// @brief makes detection square around enemy of certain size
	bool detectionZone(Entity* other, int zonesize);

private:

};
