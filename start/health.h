/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file health.h
*
* @brief bullet that can be fired by the player and enemy.
*/

#pragma once
#include "entitymain.h"

class Healthbar:
		public EntityMain
{
public:
	Healthbar();
	virtual ~Healthbar();

	virtual void update(float deltatime);


};
