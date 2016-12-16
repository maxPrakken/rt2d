#pragma once
#include "entitymain.h"

class Bullet :
	public EntityMain
{
public:
	Bullet();
	virtual ~Bullet();
	virtual void update(float deltatime);

	Vector2 velocity;
	int gravity;
};
