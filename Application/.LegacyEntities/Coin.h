#pragma once
#include "Entity.h"

class Coin: public Entity
{
	bool spin;
	float speed;
	float rot;

public:

	void setSpin(bool);
	void setSpinSpeed(float speed);
	bool isSpinning();

	Coin(Scene*, Box*, std::string);
	~Coin();
	void Update(double);
	void Render();
};

