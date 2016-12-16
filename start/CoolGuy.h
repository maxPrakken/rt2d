#pragma once
#include "entitymain.h"

class CoolGuy :
	public EntityMain
{
public:
	CoolGuy();
	virtual ~CoolGuy();
	virtual void update(float deltaTime);

	Vector2 velocity;
	int gravity;

	int spriteS;

};

