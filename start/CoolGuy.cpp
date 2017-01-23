#include "CoolGuy.h"

CoolGuy::CoolGuy() : EntityMain()
{
	addSpriteSheet("assets/player_animations_full_v2.tga", 2, 6);

	velocity = Vector2(0, 0);
	gravity = 700;
}

CoolGuy::~CoolGuy()
{

}

void CoolGuy::update(float deltaTime)
{
	//player gravity
	position += velocity * deltaTime;
	velocity.y += gravity * deltaTime;
}

void CoolGuy::left(float deltaTime) {
	this->scale = Point(-1.0f, 1.0f);
	this->position += Point2(-500, 0) * deltaTime;
}

void CoolGuy::right(float deltaTime) {
	this->scale = Point(1.0f, 1.0f);
	this->position += Point2(500, 0) * deltaTime;
}

void CoolGuy::leftR(float deltaTime) {
	this->scale = Point(1.0f, 1.0f);
	this->position += Point2(-200, 0) * deltaTime;
}

void CoolGuy::jump(float deltaTime) {
	this->velocity = Vector2(0, -500);
}
