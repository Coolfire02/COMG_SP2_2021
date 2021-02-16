#include "Player.h"


Player::Player(Vector3 position, std::string name) : Entity(scene, ENTITYTYPE::CUSTOM, name) {
	Box* box = new Box(new Position3D(-1.5, -4.2, 1), new Position3D(1.5, 1.5, -1.5));
	this->hitBox = new HitBox(box);
}

Player::~Player() {
	
}

void Player::Update(double dt) {

}

void Player::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
	this->scene->modelStack.PopMatrix();
}
 
