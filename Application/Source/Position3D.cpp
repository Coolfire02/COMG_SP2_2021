#include "Position3D.h"
#include "MyMath.h"

Position3D::Position3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Position3D::Position3D(Position3D* dup) {
	this->x = dup->getX();
	this->y = dup->getY();
	this->z = dup->getZ();
}

Position3D::Position3D() : x(0),y(0),z(0) {}
Position3D::~Position3D() {} //Intentionally left blank

Position3D* Position3D::getMidPoint(Position3D* botLeft, Position3D* topRight) {
	Position3D* mid = new Position3D;
	mid->setX((topRight->getX() + botLeft->getX()) / 2.0);
	mid->setY((topRight->getY() + botLeft->getY()) / 2.0);
	mid->setZ((topRight->getZ() + botLeft->getZ()) / 2.0);
	return mid;
}

void Position3D::setX(float x) {
	this->x = x;
}

void Position3D::setY(float y) {
	this->y = y;
}

void Position3D::setZ(float z) {
	this->z = z;
}

float Position3D::getX() {
	return x;
}

float Position3D::getY() {
	return y;
}

float Position3D::getZ() {
	return z;
}
