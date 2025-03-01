#pragma once

#include "Vector3.h"

/******************************************************************************/
/*!
\file	Vertex.h
\brief
Hanldes attributes of a Vertex Object.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Position:
\brief Position of Vertex
*/
/******************************************************************************/
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) : x{ x }, y{ y }, z{ z } {};
	void set(float x = 0, float y = 0, float z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
};

/******************************************************************************/
/*!
		Class Color:
\brief Color of Vertex
*/
/******************************************************************************/
struct Color
{
	float r, g, b;
	Color(float r = 0, float g = 0, float b = 0) : r{ r }, g{ g }, b{ b } {};
	void set(float r = 0, float g = 0, float b = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
	};
};

/******************************************************************************/
/*!
		Class TexCoord:
\brief TexCoor of Vertex
*/
/******************************************************************************/
struct TexCoord 
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; };
};

/******************************************************************************/
/*!
		Class Vertex:
\brief Hanldes attributes of a Vertex Object.
*/
/******************************************************************************/
struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
};