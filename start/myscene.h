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
#include <rt2d/text.h>

#include <vector>

#include "myentity.h"
#include "CoolGuy.h"
#include "background.h"
#include "bullet.h"
#include "platform.h"
#include "enemies.h"
#include "ebullet.h"
#include "health.h"
#include "finishline.h"

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

	/// @brief spawns player bullets
	void MyScene::bulletspawn();

	/// @brief animation controller for player
	void MyScene::animationController();

	/// @brief animation controller for enemy
	void MyScene::enemyAnimationController();

	/// @brief animation handler for player
	void MyScene::animationHandler(int y, int x);

	/// @brief test if player bullets hit enemy
	void MyScene::bulletTest();

	/// @brief spawns enemy at certain position
	void MyScene::enemySpawn(int x, int y);

	/// @brief despawns all enemies
	void MyScene::enemyDeSpawn();

	/// @brief makes it easier to print into the console
	void MyScene::print(std::string string);

	void MyScene::print(int i);

	void MyScene::print(int i, int x);

	void MyScene::print(float i);

	/// @brief enemy AI
	void MyScene::enemyMovement(float deltaTime);

	/// @brief spawns enemy bullets at enemy position
	void MyScene::enemyBulletSpawn();

	/// @brief makes enemies schoot when they are allowed to
	void MyScene::enemyBulletShootHandler();

	/// @brief despawns player bullets on hit ground
	void MyScene::bulletDespawnOnHitGround();

	void MyScene::enemyBulletDespawnOnHitGround();

	void MyScene::cameraController();

	void MyScene::platformSpawn(int x, int y);

	void MyScene::playerOnPlatform();

	void MyScene::healthAnimationController();

	void MyScene::healthAnimationHandler(int y, int x);

	void MyScene::backgroundSpawn(int xpos);

	void MyScene::worldBuild();

	void MyScene::worldDelete();

	void MyScene::enemyOnPlatform();

	void MyScene::finishCollision();

	void MyScene::PandEonGround();

	bool turned;
	bool semiTurned;
	bool Eturned;

	bool isFiring;
	bool isFiringD;
	bool fireTimer;

	bool alive;
	bool paused;
	bool finished;

	bool onP;

	int xoffset;
	int eXoffset;
	int cameraOffset;

	int toSet;

	int playerHealth;

	bool Eidle;
	bool Eshooting;
	bool Edriving;
	bool Edrivingshooting;
	bool EisFiring;

	bool inShootingRange;

	Vector2 cameraVelocity;

private:
	//MyEntity* myentity;

	Health* healthbar;

	CoolGuy* MyCoolGuy1;

	Finishline* finishline;

	std::vector<Bullet*> bulletVector;

	std::vector<Ebullet*> enemyBulletVector;

	std::vector<Enemy*> enemyVector;
	
	std::vector<Platform*> platformVector;

	std::vector<Background*> backgroundVector;

	Text* timerText;
	Text* deathText;
	Text* pauseText;
	Text* finishText;
	Text* finishText2;
	Text* finishText3;

	Timer t;
	Timer s;
	Timer k;
	Timer h;
	Timer countuptimer;
};

#endif /* SCENE00_H */
