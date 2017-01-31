/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file ebullet.h
*
* @brief bullet that can be fired by the player and enemy.
*/

#pragma once
#include "entitymain.h"

class Ebullet :
	public EntityMain
{
public:
	/// @brief Ebullet constructor
	Ebullet();
	/// @brief Ebullet virtual deconstructor
	virtual ~Ebullet();

	/// @brief update is automatically called every frame
	/// @param deltatime, time elapsed in seconds.
	/// @return void.
	virtual void update(float deltatime);

	/// @brief velocity of bullet in pixels per second.
	Vector2 velocity;

	/// @brief gravity in pixels per seconds.
	int gravity;

private:

};
