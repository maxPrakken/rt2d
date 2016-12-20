/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file platform.h
*
* @brief platform which the player can jump on.
*/

#pragma once
#include "entitymain.h"

/// @brief platform class in platform implementation.
class Platform :
	public EntityMain
{
public:
	/// @brief platform constructor.
	Platform();
	
	///@brief platform virtual deconstructor.
	virtual ~Platform();

	/// @brief update is automatically called every frame
	/// @param deltatime, time elapsed in seconds.
	/// @return void.
	virtual void update(float deltaTime);

private:

};
