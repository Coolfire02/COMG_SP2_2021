#pragma once
#include "Entity.h"

/******************************************************************************/
/*!
\file	WorldObject.h
\author Tan Yong Hong
\brief
WorldObject Entity usually used for Buildings, Trees etc.
*/
/******************************************************************************/

class WorldObject : public Entity
{
	const GEOMETRY_TYPE associatedType;
public:
	WorldObject(Scene*, GEOMETRY_TYPE, std::string);
	~WorldObject();
	void Update(double);
	void Render();
};

