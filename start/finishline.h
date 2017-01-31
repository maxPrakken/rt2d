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
	Finishline();
	virtual ~Finishline();

	virtual void update(float deltatime);

private:

};
