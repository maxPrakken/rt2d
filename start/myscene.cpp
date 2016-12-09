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

	turned = false;

	MyCoolGuy1 = new CoolGuy();
	MyCoolGuy1->position = Point2(SWIDTH / 1.5, SHEIGHT / 1.5);

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
	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		//myentity->scale = Point(0.5f, 0.5f);
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		//myentity->scale = Point(1.0f, 1.0f);
	}

	if (input()->getKey(GLFW_KEY_D)) {
		MyCoolGuy1->scale = Point(1.0f, 1.0f);
		MyCoolGuy1->position += Point2(1000, 0) * deltaTime;
	}

	if (input()->getKey(GLFW_KEY_A)) {
		MyCoolGuy1->scale = Point(-1.0f, 1.0f);
		MyCoolGuy1->position += Point2(-1000, 0) * deltaTime;
	}


	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		//RGBAColor color = myentity->sprite()->color;
		//myentity->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
}
