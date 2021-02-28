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
	Car* currentDrivingCar; // current car
	bool driving;
	// int Money; // lmao useless now
	// std::vector<Items*> Inventory; remove the // later when Items have been implemented // Haha we put inventory in game LOL

public:
	Player(Scene* scene, Vector3 position, std::string);
	~Player();
	bool isDriving();
	void setDriving(Car*, bool);
	Car* getCar();

	void Update(double);
	void Render();
};

