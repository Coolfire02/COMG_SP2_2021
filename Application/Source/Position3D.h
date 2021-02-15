#pragma once
class Position3D
{
	float x, y, z;

public:
	Position3D(float, float, float);
	Position3D(Position3D*);
	Position3D();
	~Position3D();

	void setX(float);
	void setY(float);
	void setZ(float);

	float getX();
	float getY();
	float getZ();

	static Position3D* getMidPoint(Position3D*, Position3D*);
};

