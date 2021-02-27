#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;

	//Week 7
	enum LIGHT_TYPE {
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};

	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff, cosInner, exponent;

	Light() {
		type = LIGHT_TYPE::LIGHT_POINT;
		position.set(0.0f, 20.0f, 0.0f);
		color.set(1.0f, 1.0f, 1.0f);
		power = 1;
		kC = 1.0f;
		kL = 0.01f;
		kQ = 0.001f;
		spotDirection.Set(0.0f, -1.0f, 0.0f);
		cosCutoff = cosInner = exponent = 1.0;
	}
};

#endif