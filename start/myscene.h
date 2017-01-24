/**
* Copyright 2015 Your Name <maxprakken3@hotmail.nl>
*
* @file myscene.h
*
* @brief scene file, this is where the level is build.
*/

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include <vector>

#include "myentity.h"
#include "CoolGuy.h"
#include "background.h"
#include "bullet.h"
#include "platform.h"
#include "enemies.h"
#include "ebullet.h"
#include "health.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	int ground;
	int f;
	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void MyScene::bulletspawn();

	void MyScene::animationController();

	void MyScene::enemyAnimationController();

	void MyScene::animationHandler(int y, int x);

	void MyScene::bulletTest();

	void MyScene::enemySpawn(float x, float y);

	void MyScene::enemyDeSpawn();

	void MyScene::print(std::string string);

	void MyScene::enemyMovement(float deltaTime);

	void MyScene::enemyBulletSpawn();

	void MyScene::enemyBulletShootHandler();

	void MyScene::bulletDespawnOnHitGround();

	void MyScene::enemyBulletDespawnOnHitGround();

	void MyScene::cameraController();

	void MyScene::platformSpawn(float x, float y);

	void MyScene::playerOnPlatform();

	void MyScene::healthAnimationController();

	void MyScene::healthAnimationHandler(int y, int x);

	bool turned;
	bool semiTurned;
	bool Eturned;

	bool isFiring;
	bool isFiringD;
	bool fireTimer;

	bool onP;

	int xoffset;
	int eXoffset;
	int cameraOffset;

	int playerHealth;

	bool Eidle;
	bool Eshooting;
	bool Edriving;
	bool Edrivingshooting;
	bool EisFiring;

	bool inShootingRange;

	Vector2 cameraVelocity;

private:
	/// @brief the rotating square in the middle of the screen
	//MyEntity* myentity;

	Health* healthbar;

	CoolGuy* MyCoolGuy1;

	Background* backgroundTest;

	std::vector<Bullet*> bulletVector;

	std::vector<Ebullet*> enemyBulletVector;

	std::vector<Enemy*> enemyVector;
	
	std::vector<Platform*> platformVector;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;
	Timer s;
	Timer k;
	Timer h;
};

#endif /* SCENE00_H */
