/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file enemies.h
*
* @brief entity enemies
*/

#pragma once
#include "entitymain.h"

class Finishline :
	public EntityMain
{
public:
	/// @brief Finishline constructor
	Finishline();
	/// @brief Finishline virtual deconstructor
	virtual ~Finishline();

	/// @brief update is automatically called every frame
	/// @param deltatime, the time elapsed in seconds.
	/// @return void
	virtual void update(float deltatime);

private:

};
