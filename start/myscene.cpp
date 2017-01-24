#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{

	playerHealth = 4;

	//camera offset
	cameraOffset = 300;

	//camera velocity
	cameraVelocity = Vector2(0, 0);

	//check what state the enemy is in
	Eidle = true;
	Eshooting = false;
	Edriving = false;
	Edrivingshooting = false;

	inShootingRange = false;

	// start the timer.
	t.start();

	// start enemy animation timer
	s.start();

	//start enemy shoot timer
	k.start();

	//start health animation timer
	h.start();

	//check if player has turned
	turned = false;
	semiTurned = false;

	//sets ground level
	ground = 700;

	//player initialising and attributes
	MyCoolGuy1 = new CoolGuy();
	MyCoolGuy1->position = Point2(200, 680);
	//MyCoolGuy1->scale = Point(0.5f, 0.5f);

	//health hud
	healthbar = new Health();

	//background initialise
	backgroundTest = new Background();
	backgroundTest->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	
	// create the scene 'tree'
	// add myentity to this Scene as a child. :))))
	this->addChild(backgroundTest);
	this->addChild(healthbar);
	this->addChild(MyCoolGuy1);

	//first enemy spawn out vector
	enemySpawn(500.0f, 680.0f);
	enemySpawn(200.0f, 680.0f);

	//camera position relative to player
	camera()->position = Point(MyCoolGuy1->position.x, SHEIGHT / 1.5, 1);

	//spawn platforms
	platformSpawn(500.0f, 600.0f);
}


MyScene::~MyScene()
{
	//delete bullets on close program
	for (unsigned int i = 0; i < bulletVector.size(); i++) {
		this->removeChild(bulletVector[i]);
		delete bulletVector[i];
	}
	bulletVector.clear();

	//delete enemies on close program
	for (unsigned int i = 0; i < enemyVector.size(); i++) {
		this->removeChild(enemyVector[i]);
		delete enemyVector[i];
	}

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

	healthbar->position = Point2(camera()->position.x - 500, 200);

	//velocity to camera
	camera()->position += cameraVelocity * deltaTime;

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	//basic movement right
	if (input()->getKey(GLFW_KEY_D)) {
		MyCoolGuy1->right(deltaTime);
		turned = false;
		semiTurned = false;
	}

	//basic movement left
	if (input()->getKey(GLFW_KEY_A) && input()->getKey(GLFW_KEY_LEFT_SHIFT)) {
		MyCoolGuy1->leftR(deltaTime);
		turned = false;
		semiTurned = true;
	}
	
	if (input()->getKey(GLFW_KEY_A) && !input()->getKey(GLFW_KEY_LEFT_SHIFT)) {
		MyCoolGuy1->left(deltaTime);
		turned = true;
		semiTurned = false;
	}

	//basic player jump
	if (input()->getKey(GLFW_KEY_SPACE) && MyCoolGuy1->position.y == ground || 
		(input()->getKey(GLFW_KEY_SPACE) && onP == true)) {
		MyCoolGuy1->jump(deltaTime);
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

	//make bullet come out of correct end of tank
	if (turned) {
		xoffset = -85;
		cameraOffset = -300;
	}
	else {
		xoffset = 85;
		cameraOffset = 300;
	}

	//make bullet come out of correct end of enemy
	if (Eturned) {
		eXoffset = -85;
	}
	else {
		eXoffset = 85;
	}

	playerOnPlatform();
	enemyBulletShootHandler();
	animationController();
	enemyAnimationController();
	bulletTest();
	enemyMovement(deltaTime);
	enemyBulletDespawnOnHitGround();
	bulletDespawnOnHitGround();
	cameraController();
	healthAnimationController();

}



void MyScene::healthAnimationController() {
	if (playerHealth == 4) {
		healthAnimationHandler(4, 4);
	}
	else if (playerHealth == 3) {
		healthAnimationHandler(5, 5);
	}
	else if (playerHealth == 2) {
		healthAnimationHandler(2, 2);
	}
	else if (playerHealth == 1) {
		healthAnimationHandler(0, 0);
	}
	else {
		healthAnimationHandler(1, 1);
	}
}

void MyScene::healthAnimationHandler(int y, int x) {
	static int f = y;
	if (f > x) { f = y; }
	healthbar->sprite()->frame(f);
	if (h.seconds() > 0.10f) {

		f++;
		h.start();
	}
}

void MyScene::cameraController() {
	if (!turned) {
		if (camera()->position.x != MyCoolGuy1->position.x + cameraOffset && 
			camera()->position.x < MyCoolGuy1->position.x + cameraOffset) {
			cameraVelocity = Vector2(800, 0);
		}
		else {
			cameraVelocity = Vector2(0, 0);
		}
	}
	
	if (turned || semiTurned) {
		if (camera()->position.x != MyCoolGuy1->position.x + cameraOffset &&
			camera()->position.x > MyCoolGuy1->position.x + cameraOffset) {
			cameraVelocity = Vector2(-800, 0);
		}
		else {
			cameraVelocity = Vector2(0, 0);
		}
	}
}

void MyScene::enemyBulletDespawnOnHitGround() {
	//despawn enemy bullets on hit ground
	std::vector<Ebullet*>::iterator it = enemyBulletVector.begin();
	while (it != enemyBulletVector.end())
	{
		if ((*it)->position.y >= 730 || MyCoolGuy1->isCollidingWith((*it))) {
			playerHealth -= 1;
			Ebullet* b = (*it);
			this->removeChild(b);
			it = enemyBulletVector.erase(it);
			delete b;
		}
		else
		{
			it++;
		}
	}
}

void MyScene::bulletDespawnOnHitGround() {
	//despawn bullets on hit ground
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	while (it != bulletVector.end())
	{
		if ((*it)->position.y >= 730) {
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
		bullet1->position = Point2(MyCoolGuy1->position.x + xoffset, MyCoolGuy1->position.y - 20);
		bullet1->scale = Point(1.0f, 1.0f);
		
		//make bullets face correct direction
		if (turned) {
			bullet1->velocity = Vector2(-900, 0);
			bullet1->scale = Point(-1.0f, -1.0f);
		}
		else {
			bullet1->velocity = Vector2(900, 0);
			bullet1->scale = Point(1.0f, 1.0f);
		}

		//add child to vector
		this->addChild(bullet1);
		bulletVector.push_back(bullet1);
		print("adding bullets to vector");
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
	int todelete = 0;

	std::vector<Enemy*>::iterator that = enemyVector.begin();
	while (that != enemyVector.end()) {
		todelete = 0;
		std::vector<Bullet*>::iterator it = bulletVector.begin();
		while (it != bulletVector.end()) {
			if ((*it)->isCollidingWith((*that))) {
				Bullet* b = (*it);
				this->removeChild(b);
				it = bulletVector.erase(it);
				delete b;
				print("hitting");
				todelete = 1;
			}
			else {
				it++;
			}
		}
		if (todelete == 1) {
			Enemy* e = (*that);
			this->removeChild(e);
			that = enemyVector.erase(that);
			delete e;
		}
		else {
			that++;
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

void MyScene::platformSpawn(float x, float y) {
	Platform* platform = new Platform();
	platform->position = Point2(x, y);

	this->addChild(platform);
	platformVector.push_back(platform);
	print("spawning a platform");
}

void MyScene::playerOnPlatform() {
	//player collision with platform
	std::vector<Platform*>::iterator it = platformVector.begin();
	while (it != platformVector.end()) {
		if (MyCoolGuy1->isCollidingWith((*it))) {
			onP = true;
			MyCoolGuy1->velocity.y = 0;
			MyCoolGuy1->position = Point2(MyCoolGuy1->position.x, (*it)->position.y - 80);
		}
		else {
			onP = false;
		}
		it++;
	}
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

void MyScene::enemyBulletSpawn() {
	std::vector<Enemy*>::iterator it = enemyVector.begin();
	while (it != enemyVector.end()) {
		if (k.seconds() > 1.0f) {
			k.start();
			Enemy* e = (*it);

			Ebullet* Ebullet1 = new Ebullet();
			Ebullet1->position = Point2(e->position.x + eXoffset, e->position.y - 10);
			Ebullet1->scale = Point(1.0f, 1.0f);
			this->addChild(Ebullet1);
			enemyBulletVector.push_back(Ebullet1);

			if (Eturned) {
				Ebullet1->velocity = Vector2(-900, 0);
				Ebullet1->scale = Point(-1.0f, -1.0f);
			}
			else {
				Ebullet1->velocity = Vector2(900, 0);
				Ebullet1->scale = Point(1.0f, 1.0f);
			}
			
		}
		else {
			it++;

		}
	}
}

void MyScene::enemyBulletShootHandler() {
	if (inShootingRange == true) {
		enemyBulletSpawn();
	}
}

void MyScene::enemyMovement(float deltaTime) {
	for (int i = 0; i < enemyVector.size(); i++) {
		//stop zone, stops the enemy if he is close enough and starts shooting
		if (enemyVector[i]->detectionZone(MyCoolGuy1, 2)) {
			//enemyShoot();
			//print("enemy is shooting short");
			inShootingRange = true;
		}

		//will make enemy go towards player while shooting
		if (enemyVector[i]->detectionZone(MyCoolGuy1, 8) && !enemyVector[i]->detectionZone(MyCoolGuy1, 2)) {
			//enemyShoot();
			//print("enemy is shooting long");
			inShootingRange = true;

			if (enemyVector[i]->position.x > MyCoolGuy1->position.x) {
				enemyVector[i]->position += Point2(-300, 0) * deltaTime;
				enemyVector[i]->scale = Point(1.0f, 1.0f);
				Eturned = true;
			}
			else {
				enemyVector[i]->position += Point2(300, 0) * deltaTime;
				enemyVector[i]->scale = Point(-1.0f, 1.0f);
				Eturned = false;
			}
		}

		//enemy detects player, will move toword player
		if (enemyVector[i]->detectionZone(MyCoolGuy1, 10) && !enemyVector[i]->detectionZone(MyCoolGuy1, 2) && !enemyVector[i]->detectionZone(MyCoolGuy1, 8)) {
			inShootingRange = false;
			//print("enemy has detected you and is comming for your ass :D");

			if (enemyVector[i]->position.x > MyCoolGuy1->position.x) {
				enemyVector[i]->position += Point2(-300, 0) * deltaTime;
				enemyVector[i]->scale = Point(1.0f, 1.0f);
				Eturned = true;
			}
			else {
				enemyVector[i]->position += Point2(300, 0) * deltaTime;
				enemyVector[i]->scale = Point(-1.0f, 1.0f);
				Eturned = false;
			}
		}
	}
}







