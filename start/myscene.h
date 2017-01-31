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
	
	/// @brief despawns enemy bullets when they hit the ground
	void MyScene::enemyBulletDespawnOnHitGround();

	/// @brief camera pan in the right direction
	void MyScene::cameraController();

	/// @brief spawns platform at set position
	void MyScene::platformSpawn(int x, int y);

	/// @brief keeps player on platform
	void MyScene::playerOnPlatform();

	/// @brief goes through healthbar animations
	void MyScene::healthAnimationController();

	/// @brief handles the healthAnimationController
	void MyScene::healthAnimationHandler(int y, int x);

	/// @brief spawns background at set position
	void MyScene::backgroundSpawn(int xpos);

	/// @brief load the constructor
	void MyScene::worldBuild();

	/// @brief loads the deconstructor
	void MyScene::worldDelete();

	/// @brief holds enemies on platform
	void MyScene::enemyOnPlatform();

	/// @brief checks if you're colliding with the finish line
	void MyScene::finishLineCollision();

	/// @brief keeps player and enemy on the ground during pause or death
	void MyScene::PandEonGround();

	/// @brief checks if enemy bullet hits player
	void MyScene::enemyHitPlayer();

	/// @brief checks if player is turned around
	bool turned;
	/// @brief checks if player is holding shift while turning around
	bool semiTurned;
	/// @brief checks if enemy is turned around
	bool Eturned;

	/// @brief checks if you're firing
	bool isFiring;
	/// @brief checks if you're firing while driving
	bool isFiringD;
	/// @brief gives shooting a delay
	bool fireTimer;

	/// @brief checks if player is alive
	bool alive;
	/// @brief check if game is paused
	bool paused;
	/// @brief check if game is finished
	bool finished;

	/// @brief checks if player is on a platform
	bool onP;

	/// @brief makes bullet come out of right side of the tank
	int xoffset;
	/// @brief checks if enemy bullet comes out of right side of the enemy tank
	int eXoffset;
	/// @brief gives a offset to the camera
	int cameraOffset;

	/// @brief makes enemies not fall through platforms
	int toSet;

	/// @brief amound of health the player has
	int playerHealth;

	/// @brief checks if enemy is idle
	bool Eidle;
	/// @brief checks if enemy is shooting
	bool Eshooting;
	/// @brief checks if enemy is driving
	bool Edriving;
	/// @brief checks if enemy is drving and shooting at the same time
	bool Edrivingshooting;
	/// @brief boolean to keep animation overwriting in check
	bool EisFiring;

	/// @brief checks if player is in shooting range of enemies
	bool inShootingRange;

	/// @brief speed of the camera
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
