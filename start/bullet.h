/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file bullet.h
*
* @brief bullet that can be fired by the player and enemy.
*/

#pragma once
#include "entitymain.h"

/// @brief bullet class in bullet implementation.
class Bullet :
	public EntityMain
{
public:
	/// @brief bullet constructor
	Bullet();

	/// @brief bullet virtual deconstructor
	virtual ~Bullet();

	/// @brief update is automatically called every frame
	/// @param deltatime, the time elapsed in seconds.
	/// @return void
	virtual void update(float deltatime);

	/// @brief velocity of bullet in pixels per second.
	Vector2 velocity;

	/// @brief gravity in pixels per seconds.
	int gravity;
};
