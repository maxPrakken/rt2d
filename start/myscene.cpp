#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	//check if player has turned
	turned = false;

	ground = 700;

	//player initialising and attributes
	MyCoolGuy1 = new CoolGuy();
	MyCoolGuy1->position = Point2(200, 680);
	MyCoolGuy1->scale = Point(0.5f, 0.5f);

	//background initialise
	backgroundTest = new Background();
	backgroundTest->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	
	// create the scene 'tree'
	// add myentity to this Scene as a child. :))))
	this->addChild(backgroundTest);
	this->addChild(MyCoolGuy1);
}


MyScene::~MyScene()
{
	//delete bullets on close program
	for (unsigned int i = 0; i < bulletVector.size(); i++) {
		this->removeChild(bulletVector[i]);
		delete bulletVector[i];
	}
	bulletVector.clear();

	

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

	//basic movement right
	if (input()->getKey(GLFW_KEY_D)) {
		MyCoolGuy1->scale = Point(0.5f, 0.5f);
		MyCoolGuy1->position += Point2(500, 0) * deltaTime;
		turned = false;
	}

	//basic movement left
	if (input()->getKey(GLFW_KEY_A)) {
		MyCoolGuy1->scale = Point(-0.5f, 0.5f);
		MyCoolGuy1->position += Point2(-500, 0) * deltaTime;
		turned = true;
	}

	//basic player jump
	if (input()->getKey(GLFW_KEY_SPACE)) {
		if (MyCoolGuy1->position.y == ground) {
			MyCoolGuy1->velocity = Vector2(0, -500);
		}
	}

	//player shoot
	if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		bulletspawn();
	}

	//keep player on ground level
	if (MyCoolGuy1->position.y > ground) {
		MyCoolGuy1->velocity.y = 0;
		MyCoolGuy1->position = Point2(MyCoolGuy1->position.x, ground);
	}

	//camera position relative to player
	camera()->position = Point(MyCoolGuy1->position.x + 300, SHEIGHT / 1.5, 1);

	//make bullet come out of correct end of tank
	if (turned) {
		xoffset = -50;
	}
	else {
		xoffset = 50;
	}
}

//spawn bullets
void MyScene::bulletspawn() {	
		Bullet* bullet1 = new Bullet();
		bullet1->position = Point2(MyCoolGuy1->position.x + xoffset, MyCoolGuy1->position.y - 20);
		bullet1->scale = Point(0.5f, 0.5f);
		
		//make bullets face correct direction
		if (turned) {
			bullet1->velocity = Vector2(-900, 0);
			bullet1->scale = Point(-0.5f, -0.5f);
		}
		else {
			bullet1->velocity = Vector2(900, 0);
			bullet1->scale = Point(0.5f, 0.5f);
		}

		//add child to vector
		this->addChild(bullet1);
		bulletVector.push_back(bullet1);
}
