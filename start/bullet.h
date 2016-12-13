#pragma once
#include "entity.h"

class Bullet :
	public Entity
{
public:
	Bullet();
	virtual ~Bullet();
	virtual void update(float deltatime);

	Vector2 velocity;
	int gravity;
};
