/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	//check if player has turned
	turned = false;

	//player initialising and attributes
	MyCoolGuy1 = new CoolGuy();
	MyCoolGuy1->position = Point2(200, 680);
	MyCoolGuy1->scale = Point(0.5f, 0.5f);

	backgroundTest = new Background();
	backgroundTest->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	// create the scene 'tree'
	// add myentity to this Scene as a child. :))))
	this->addChild(backgroundTest);
	this->addChild(MyCoolGuy1);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	//this->removeChild(myentity);
	this->removeChild(MyCoolGuy1);

	// delete myentity from the heap (there was a 'new' in the constructor)
	//delete myentity;
	delete MyCoolGuy1;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// Spacebar scales myentity
	// ###############################################################

	//basic movement right
	if (input()->getKey(GLFW_KEY_D)) {
		MyCoolGuy1->scale = Point(0.5f, 0.5f);
		MyCoolGuy1->position += Point2(500, 0) * deltaTime;
	}

	//basic movement left
	if (input()->getKey(GLFW_KEY_A)) {
		MyCoolGuy1->scale = Point(-0.5f, 0.5f);
		MyCoolGuy1->position += Point2(-500, 0) * deltaTime;
	}

	//player gravity
	if (!MyCoolGuy1->position.y >= 690) {
		MyCoolGuy1->position += Point2(0, 100) * deltaTime;
	}

	//camera position relative to player
	camera()->position = Point(MyCoolGuy1->position.x + 300, SHEIGHT / 1.5, 1);


	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		//RGBAColor color = myentity->sprite()->color;
		//myentity->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
}
