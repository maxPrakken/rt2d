#pragma once
#include "entity.h"

class Background :
	public Entity
{
public:
	Background();
	virtual ~Background();
	virtual void update(float deltaTime);

};