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

	bool turned;

	bool isFiring;
	bool isFiringD;
	bool fireTimer;

	bool onP;

	int xoffset;

	bool Eidle;
	bool Eshooting;
	bool Edriving;
	bool Edrivingshooting;
	bool EisFiring;

private:
	/// @brief the rotating square in the middle of the screen
	//MyEntity* myentity;

	Platform* platform1;

	CoolGuy* MyCoolGuy1;

	Background* backgroundTest;

	std::vector<Bullet*> bulletVector;

	std::vector<Enemy*> enemyVector;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;

	Timer s;
};

#endif /* SCENE00_H */
