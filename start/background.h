/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file background.h
*
* @brief background of the level.
*/

#pragma once
#include "entity.h"

/// @brief background class in background implementation.
class Background :
	public Entity
{
public:
	/// @brief background constructor.
	Background();

	/// @brief virtual backround deconstructor.
	virtual ~Background();

	/// @brief update is automatically called every frame
	/// @param deltatime, the time elapsed in seconds.
	/// @return void
	virtual void update(float deltaTime);

};