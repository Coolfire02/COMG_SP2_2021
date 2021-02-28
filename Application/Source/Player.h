#pragma once
#include "Entity.h"
#include "Car.h"
// Created by Joash on 16/2/21

class Car;

/******************************************************************************/
/*!
\file	Player.h
\author Joash Foo
\brief
Handles all Players functionalities.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Player:
\brief Handles all Players functionalities.
*/
/******************************************************************************/
class Player : public Entity
{
private:
	Car* currentDrivingCar;
	bool driving;
	int Money;
	// std::vector<Items*> Inventory; remove the // later when Items have been implemented

public:
	Player(Scene* scene, Vector3 position, std::string);
	~Player();
	bool isDriving();
	void setDriving(Car*, bool);
	Car* getCar();

	void Update(double);
	void Render();
};

