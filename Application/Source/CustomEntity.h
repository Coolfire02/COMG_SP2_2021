#pragma once
#include "Entity.h"

/******************************************************************************/
/*!
\file	CustomEntity.h
\author Tan Yong Hong
\brief
Sub-Type of an Entity. Usually used to create Interaction Zones in the worl
by spawning a Custom Entity with only a HitBox.
*/
/******************************************************************************/

class CustomEntity : public Entity
{
public:
	CustomEntity(Scene*, Box*, std::string);
	~CustomEntity();
	void Update(double);
	void Render();
};

