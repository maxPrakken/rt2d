#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{

	//check what state the enemy is in
	Eidle = true;
	Eshooting = false;
	Edriving = false;
	Edrivingshooting = false;

	// start the timer.
	t.start();

	// start enemy animation timer
	s.start();

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

	//first enemy spawn out vector
	enemySpawn(500.0f, 680.0f);
	
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
	for (int i = 0; i < enemyVector.size(); i++) {
		//stop zone, stops the enemy if he is close enough and starts shooting
		if (enemyVector[i]->detectionZone(MyCoolGuy1, 2)) {
			//enemyShoot();
			print("enemy is shooting short");
		}

		//will make enemy go towards player while shooting
		if (enemyVector[i]->detectionZone(MyCoolGuy1, 5) && !enemyVector[i]->detectionZone(MyCoolGuy1, 2)) {
			//enemyShoot();
			print("enemy is shooting long");

			if (enemyVector[i]->position.x > MyCoolGuy1->position.x) {
				enemyVector[i]->position += Point2(-300, 0) * deltaTime;
				enemyVector[i]->scale = Point(1.0f, 1.0f);
			}
			else {
				enemyVector[i]->position += Point2(300, 0) * deltaTime;
				enemyVector[i]->scale = Point(-1.0f, 1.0f);
			}
		}

		//enemy detects player, will move toword player
		if (enemyVector[i]->detectionZone(MyCoolGuy1, 8) && !enemyVector[i]->detectionZone(MyCoolGuy1, 2) && !enemyVector[i]->detectionZone(MyCoolGuy1, 5)) {

			print("enemy has detected you and is comming for your ass :D");

			if (enemyVector[i]->position.x > MyCoolGuy1->position.x) {
				enemyVector[i]->position += Point2(-300, 0) * deltaTime;
				enemyVector[i]->scale = Point(1.0f, 1.0f);
			}
			else {
				enemyVector[i]->position += Point2(300, 0) * deltaTime;
				enemyVector[i]->scale = Point(-1.0f, 1.0f);
			}
		}
	}

	//player collision with platform
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
		MyCoolGuy1->scale = Point(1.0f, 1.0f);
		MyCoolGuy1->position += Point2(500, 0) * deltaTime;
		turned = false;
	}

	//basic movement left
	if (input()->getKey(GLFW_KEY_A) && input()->getKey(GLFW_KEY_LEFT_SHIFT)) {
		MyCoolGuy1->scale = Point(1.0f, 1.0f);
		MyCoolGuy1->position += Point2(-200, 0) * deltaTime;
		turned = false;
	}
	
	if (input()->getKey(GLFW_KEY_A) && !input()->getKey(GLFW_KEY_LEFT_SHIFT)) {
		MyCoolGuy1->scale = Point(-1.0f, 1.0f);
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
	for (int i = 0; i < enemyVector.size(); i++) {
		if (enemyVector[i]->position.y > ground) {
			enemyVector[i]->velocity.y = 0;
			enemyVector[i]->position = Point2(enemyVector[i]->position.x, ground);
		}
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
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	while (it != bulletVector.end())
	{
		if ((*it)->position.y >= ground) {
			Bullet* b = (*it);
			this->removeChild(b);
			it = bulletVector.erase(it);
			delete b;
		}
		else
		{
			it++;
		}
	}
	
	animationController();
	enemyAnimationController();
	bulletTest();
}

void MyScene::animationController() {

	//keeps animation overlaying while driving and shooting at bay
	if (isFiringD)
	{
		MyCoolGuy1->sprite()->frame(8);
		if (t.seconds() > 0.2f) {
			isFiringD = false;
			t.start();
		}
		else
			return;
	}

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

		animationHandler(4, 7);
	}

	//animation for driving and shooting
	if (input()->getKey(GLFW_KEY_A) && input()->getMouseDown(GLFW_MOUSE_BUTTON_1) || input()->getKey(GLFW_KEY_D) && input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		isFiring = true;
		animationHandler(9, 9);
	}

	//animation for firing;
	else if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		isFiring = true;
		animationHandler(8, 8);
	}

	//animation for idle
	else if (!input()->getMouseDown(GLFW_MOUSE_BUTTON_1) && !(input()->getKey(GLFW_KEY_A) || input()->getKey(GLFW_KEY_D))) {
		animationHandler(0, 3);
	}
	

	//animation for firing;
	else if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		isFiring = true;
		animationHandler(8, 8);
	}

	//animation for idle
	else if (!input()->getMouseDown(GLFW_MOUSE_BUTTON_1) && !(input()->getKey(GLFW_KEY_A) || input()->getKey(GLFW_KEY_D))) {
		animationHandler(0, 3);
	}
}

void MyScene::enemyAnimationController() {

	//animation for idle
	if (Eidle) {
		for (int i = 0; i < enemyVector.size(); i++) {
			static int f = 0;
			if (f > 3) { f = 0; }
			enemyVector[i]->sprite()->frame(f);
			if (s.seconds() > 0.10f) {

				f++;
				s.start();
			}
		}
	}
}

//spawn bullets
void MyScene::bulletspawn() {	
		Bullet* bullet1 = new Bullet();
		bullet1->position = Point2(MyCoolGuy1->position.x + xoffset, MyCoolGuy1->position.y - 10);
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

//makes making animations for the player easier. 
//int y is your starting point and int x is your ending point.
void MyScene::animationHandler( int y, int x) {
	static int f = y;
	if (f > x) { f = y; }
	MyCoolGuy1->sprite()->frame(f);
	if (t.seconds() > 0.10f) {

		f++;
		t.start();
	}
}

void MyScene::bulletTest() {
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	while (it != bulletVector.end()) {
		for (int i = 0; i < enemyVector.size(); i++) {
			if ((*it)->isCollidingWith(enemyVector[i])) {
				Bullet* b = (*it);
				this->removeChild(b);
				it = bulletVector.erase(it);
				delete b;

				enemyDeSpawn();
			}
			else
			{
				it++;
			}
		}
	}
}

void MyScene::enemySpawn(float x, float y) {
	Enemy* enemy = new Enemy();
	enemy->position = Point2(x, y);

	this->addChild(enemy);
	enemyVector.push_back(enemy);
	print("im spawning a enemy");
}

void MyScene::enemyDeSpawn() {
	std::vector<Enemy*>::iterator it = enemyVector.begin();
	while (it != enemyVector.end()) {
		Enemy* e = (*it);
		this->removeChild(e);
		it = enemyVector.erase(it);
		delete e;
	}
}

void MyScene::print(std::string string) {
	std::cout << string << std::endl;
}



