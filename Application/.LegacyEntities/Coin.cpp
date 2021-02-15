#include "Coin.h"

//Speed is the amount of rounds to spin per second
Coin::Coin(Scene* scene, Box* hitBox, std::string name) : Entity(scene, ENTITYTYPE::COIN, name), spin(true), speed(30.f) {
	this->hitBox = new HitBox(hitBox);
	this->rot = 0.0;
}
	
Coin::~Coin() {}

void Coin::setSpin(bool toggle) {
	spin = toggle;
}

void Coin::setSpinSpeed(float speed) {
	this->speed = speed;
}

bool Coin::isSpinning() {
	return spin;
}

void Coin::Update(double dt) {
	if (spin) {
		rot += speed * dt;
		if (rot > 360) rot -= 360;
		this->data->rotZMag = rot;
		int num = rot / 90;
		if ( num % 2 == 0 ) this->data->transY -= (float) 0.2 * (float)dt;
		else this->data->transY += 0.2 * (float) dt;
	}
}

void Coin::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_COIN), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}
