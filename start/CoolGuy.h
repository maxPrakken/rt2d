#pragma once
#include "entity.h"

class CoolGuy :
	public Entity
{
public:
	CoolGuy();
	virtual ~CoolGuy();
	virtual void update(float deltaTime);
	 
};

