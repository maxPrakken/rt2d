#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{

	//enemy spawn test, ///////////////// remove this
	testE = new Enemies();
	testE->position = Point2(500, 680);

	//check what state the enemy is in
	Eidle = true;
	Eshooting = false;
	Edriving = false;
	Edrivingshooting = false;

	// start the timer.
	t.start();

	//check if player has turned
	turned = false;

	//sets ground level
	ground = 700;

	//first platform initialising and stuffs
	platform1 = new Platform();
	platform1->position = Point2(500, 600);
	//platform1->scale = Point(0.5f, 0.5f);

	//player initialising and attributes
	MyCoolGuy1 = new CoolGuy();
	MyCoolGuy1->position = Point2(200, 680);
	//MyCoolGuy1->scale = Point(0.5f, 0.5f);

	//background initialise
	backgroundTest = new Background();
	backgroundTest->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	
	// create the scene 'tree'
	// add myentity to this Scene as a child. :))))
	this->addChild(backgroundTest);
	this->addChild(MyCoolGuy1);
	this->addChild(platform1);
	
	this->addChild(testE);
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

	this->removeChild(backgroundTest);

	// delete myentity from the heap (there was a 'new' in the constructor)
	//delete myentity;
	delete MyCoolGuy1;
	delete backgroundTest;
}

void MyScene::update(float deltaTime)
{

	std::cout << testE->position << std::endl;
	if (MyCoolGuy1->isCollidingWith(platform1)) {
		onP = true;
		MyCoolGuy1->velocity.y = 0;
		MyCoolGuy1->position = Point2(MyCoolGuy1->position.x, platform1->position.y - 80);
	}
	else { onP = false; }

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	//basic movement right
	if (input()->getKey(GLFW_KEY_D)) {
		//MyCoolGuy1->scale = Point(1.0f, 1.0f);
		MyCoolGuy1->position += Point2(500, 0) * deltaTime;
		turned = false;
	}

	//basic movement left
	if (input()->getKey(GLFW_KEY_A)) {
		//MyCoolGuy1->scale = Point(-1.0f, 1.0f);
		MyCoolGuy1->position += Point2(-500, 0) * deltaTime;
		turned = true;
	}

	//basic player jump
	if (input()->getKey(GLFW_KEY_SPACE) && MyCoolGuy1->position.y == ground || 
		(input()->getKey(GLFW_KEY_SPACE) && onP == true)) {
			MyCoolGuy1->velocity = Vector2(0, -500);
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

	//keeps test enemy on the ground
	if (testE->position.y > ground) {
		testE->velocity.y = 0;
		testE->position = Point2(testE->position.x, ground);
	}
	
	//camera position relative to player
	camera()->position = Point(MyCoolGuy1->position.x + 300, SHEIGHT / 1.5, 1);

	//make bullet come out of correct end of tank
	if (turned) {
		xoffset = -85;
	}
	else {
		xoffset = 85;
	}

	//despawn bullets on hit ground
	for (unsigned int i = 0; i < bulletVector.size(); i++) {
		if (bulletVector[i]->position.y >= ground) {
			this->removeChild(bulletVector[i]);
			delete bulletVector[i];
		}
		bulletVector.clear();
	}
	
	animationController();
	enemyAnimationController();
}

void MyScene::animationController() {

	//keeps animation overlaying while idle and shooting at bay
	if (isFiring)
	{
		MyCoolGuy1->sprite()->frame(8);
		if (t.seconds() > 0.2f) {
			isFiring = false;
			t.start();
		}
		else
			return;
	}

	//animation for driving
	if (input()->getKey(GLFW_KEY_A) || input()->getKey(GLFW_KEY_D)) {

		static int f = 4;
		if (f > 7) { f = 4; }

		MyCoolGuy1->sprite()->frame(f);
		if (t.seconds() > 0.10f) {

			f++;
			t.start();
		}
	}

	//animation for driving and shooting
	if (input()->getKey(GLFW_KEY_A) && input()->getMouseDown(GLFW_MOUSE_BUTTON_1) || input()->getKey(GLFW_KEY_D) && input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		isFiring = true;
		static int f = 9;
		if (f > 9) { f = 9; }

		MyCoolGuy1->sprite()->frame(f);
		if (t.seconds() > 0.10f) {

			f++;
			t.start();
		}
	}

	//animation for firing;
	else if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		isFiring = true;
		static int f = 8;
		if (f > 8) { f = 8; }
		MyCoolGuy1->sprite()->frame(f);
		if (t.seconds() > 0.10f) {

			f++;
			t.start();
		}
	}

	//animation for idle
	else if (!input()->getMouseDown(GLFW_MOUSE_BUTTON_1) && !(input()->getKey(GLFW_KEY_A) || input()->getKey(GLFW_KEY_D))) {

		static int f = 0;
		if (f > 3) { f = 0; }
		MyCoolGuy1->sprite()->frame(f);
		if (t.seconds() > 0.10f) {

			f++;
			t.start();
		}
	}
}

void MyScene::enemyAnimationController() {

	//animation for idle
	if (Eidle) {

		static int f = 0;
		if (f > 3) { f = 0; }
		testE->sprite()->frame(f);
		if (t.seconds() > 0.10f) {

			f++;
			t.start();
		}
	}
}

//spawn bullets
void MyScene::bulletspawn() {	
		Bullet* bullet1 = new Bullet();
		bullet1->position = Point2(MyCoolGuy1->position.x + xoffset, MyCoolGuy1->position.y - 30);
		//bullet1->scale = Point(0.5f, 0.5f);
		
		//make bullets face correct direction
		if (turned) {
			bullet1->velocity = Vector2(-900, 0);
			//bullet1->scale = Point(-0.5f, -0.5f);
		}
		else {
			bullet1->velocity = Vector2(900, 0);
			//bullet1->scale = Point(0.5f, 0.5f);
		}

		//add child to vector
		this->addChild(bullet1);
		bulletVector.push_back(bullet1);
}
