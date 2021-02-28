#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vertex.h"

/******************************************************************************/
/*!
\file	Material.h
\brief
Game object's Material attributes.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Component:
\brief R,G,B Values of Material
*/
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
	Component& operator=(const Component& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		return *this;
	}
};

/*
/ Materials should have componenets of the ones listed below
*/

/******************************************************************************/
/*!
		Class Material:
\brief Game Object's material attributes
*/
/******************************************************************************/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	unsigned size; //indexSize
	float kShininess;
	Material() {
		kAmbient = Component(0.1f, 0.1f, 0.1f);
		kDiffuse = Component(0.6f, 0.6f, 0.6f);
		kSpecular = Component(0.3f, 0.3f, 0.3f);
		size = 0;
		kShininess = 1.0f;
	};
	Material& operator=(const Material& rhs)
	{
		kAmbient = rhs.kAmbient;
		kDiffuse = rhs.kDiffuse;
		kSpecular = rhs.kSpecular;
		kShininess = rhs.kShininess;
		size = rhs.size;
		return *this;
	}
};


#endif