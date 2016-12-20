/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file CoolGuy.h
*
* @brief entity player
*/

#pragma once
#include "entitymain.h"

/// @brief coolguy class in coolguy implementation.
class CoolGuy :
	public EntityMain
{
public:
	/// @brief coolguy constructor.
	CoolGuy();

	/// @brief virtual coolguy deconstructor.
	virtual ~CoolGuy();

	/// @brief update is automatically called every frame
	/// @param deltatime, time elapsed in seconds.
	/// @return void.
	virtual void update(float deltaTime);
	
	/// @brief speed of coolguy in pixels per second.
	Vector2 velocity;

	/// @brief amound of gravity on coolguy in pixels per second.
	int gravity;

	/// @brief int that indicates where on the spritesheet you are with a animation.
	int spriteS;

};

