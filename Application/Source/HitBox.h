#pragma once
#include "Position3D.h"
#include "Mtx44.h"
#include <vector>

struct Box {
	Position3D* botLeftPos;
	Position3D* topRightPos;
	
	Box(Position3D* botLeft, Position3D* topRight) : botLeftPos(botLeft), topRightPos(topRight) {}

	bool locIsInBox(Position3D loc) {
		if (loc.getX() >= botLeftPos->getX() && loc.getX() <= topRightPos->getX() &&
			loc.getY() >= botLeftPos->getY() && loc.getY() <= topRightPos->getY() &&
			loc.getZ() <= botLeftPos->getZ() && loc.getZ() >= topRightPos->getZ()) //Right hand rule
			return true;
		return false;
	}

	bool boxLocIsInBox(Position3D loc, Box* box) {
		float lowX, highX, lowZ, highZ;
		lowX = highX = lowZ = highZ = 0.0;
		lowX = Math::Min(box->botLeftPos->getX(), box->topRightPos->getX());
		highX = Math::Max(box->botLeftPos->getX(), box->topRightPos->getX());

		lowZ = Math::Min(box->botLeftPos->getZ(), box->topRightPos->getZ());
		highZ = Math::Max(box->botLeftPos->getZ(), box->topRightPos->getZ());

		if (loc.getX() >= lowX && loc.getX() <= highX &&
			//loc.getY() >= box->botLeftPos->getY() && loc.getY() <= box->topRightPos->getY() && disregard Y value for now, simplify
			
			
			loc.getZ() <= highZ && loc.getZ() >= lowZ) //Right hand rule
			return true;
		return false;
	}

	bool locIsInBox(Box* box) {

		std::vector<Position3D*> pos;
		Position3D* botLeftFront = this->botLeftPos; pos.push_back(botLeftFront);
		Position3D* topRightBack = this->topRightPos; pos.push_back(topRightBack);

		Position3D botRightFront = Position3D(topRightBack->getX(), botLeftFront->getY(), botLeftFront->getZ()); pos.push_back(&botRightFront);
		Position3D topLeftBack = Position3D(botLeftFront->getX(), topRightBack->getY(), topRightBack->getZ()); pos.push_back(&topLeftBack);

		Position3D botLeftBack = Position3D(botLeftFront->getX(), botLeftFront->getY(), topLeftBack.getZ()); pos.push_back(&botLeftBack);
		Position3D botRightBack = Position3D(botRightFront.getX(), botRightFront.getY(), topRightBack->getZ()); pos.push_back(&botRightBack);

		Position3D topRightFront = Position3D(topRightBack->getX(), topRightBack->getY(), botLeftFront->getZ()); pos.push_back(&topRightFront);
		Position3D topLeftFront = Position3D(topLeftBack.getX(), topLeftBack.getY(), botLeftFront->getZ()); pos.push_back(&topLeftFront);

		Position3D* thisMP = Position3D::getMidPoint(botLeftPos, topRightPos);
		Position3D* boxMP = Position3D::getMidPoint(box->botLeftPos, box->topRightPos);

		float bestX, bestY, bestZ;
		bestX = boxMP->getX();
		bestY = boxMP->getY();
		bestZ = boxMP->getZ();

		//HEHE OMG THIS WORKS
		if (bestX > topRightBack->getX()) bestX = topRightBack->getX();
		else if (bestX < botLeftFront->getX()) bestX = botLeftFront->getX();

		if (bestY > topRightBack->getY()) bestY = topRightBack->getY();
		else if (bestY < botLeftFront->getY()) bestY = botLeftFront->getY();

		if (bestZ < topRightBack->getZ()) bestZ = topRightBack->getZ();
		else if (bestZ > botLeftFront->getZ()) bestZ = botLeftFront->getZ();

		//P is for boxMP  let's call P the point you wish to find the closest point to on the rectangle.
		
		/*Position3D distanceToPositiveBounds = Position3D(thisMP->getX()+thisMP->getX()/2.0-boxMP->getX(),
														thisMP->getY()+thisMP->getY()/2.0-boxMP->getY(),
														thisMP->getZ()+thisMP->getZ()/2.0-boxMP->getZ());

		Position3D distanceToNegativeBounds = Position3D(-1.f * thisMP->getX()-thisMP->getX()/2.0-boxMP->getX(),
														-1.f * thisMP->getY()-thisMP->getY()/2.0-boxMP->getY(),
														-1.f * thisMP->getZ()-thisMP->getZ()/2.0-boxMP->getZ());

		float smallestX = Math::Min(Math::FAbs(distanceToPositiveBounds.getX()), Math::FAbs(distanceToNegativeBounds.getX()));
		float smallestY = Math::Min(Math::FAbs(distanceToPositiveBounds.getY()), Math::FAbs(distanceToNegativeBounds.getY()));
		float smallestZ = Math::Min(Math::FAbs(distanceToPositiveBounds.getZ()), Math::FAbs(distanceToNegativeBounds.getZ()));
		if (smallestX += thisMP->getX() == distanceToPositiveBounds.getX())
			bestX = thisMP->getX() + thisMP->getX() / 2.0;
		else 
			bestX = thisMP->getX() - thisMP->getX() / 2.0;

		if (smallestY += thisMP->getY() == distanceToPositiveBounds.getY())
			bestY = thisMP->getY() + thisMP->getY() / 2.0;
		else
			bestY = thisMP->getY() - thisMP->getY() / 2.0;

		if (smallestZ += thisMP->getZ() == distanceToPositiveBounds.getZ())
			bestZ = thisMP->getZ() + thisMP->getZ() / 2.0;
		else
			bestZ = thisMP->getZ() - thisMP->getZ() / 2.0;*/
		
		Position3D cloest = Position3D(bestX, bestY, bestZ); pos.push_back(&cloest);

		pos.push_back(thisMP);

		bool intersect = false;
		for (auto& entry : pos) {
			if (boxLocIsInBox(*entry, box)) {
				intersect = true;
				break;
			}
		}
		delete thisMP;
		delete boxMP;
		return intersect;
	}

	~Box() {
		if(botLeftPos != nullptr)
			delete botLeftPos;
		if(topRightPos != nullptr)
			delete topRightPos;
	}
};

/**
* Assume that all HitBoxes are "Boxes", found at the origin of an object, these Boxes can only be scaled,
* and cannot be associated with Hierarchical Models (Aka no HitBox for each mesh, but a general rectangle) for entire Entity.
* Issues with this are: L shaped objects will have to sacrifice either the horizontal or vertical collision as
* this HitBox only supports One. Single. Square. Box. Per. Entity. If you wish to work on this further for SP go ahead
* but I'm dying rn trying to come up with a proper collision system (How to interact with an Mtx44 (Based of projection/model stack or wtever) & Mesh BotLeft & Top Right Cords to come up with Hitbox?)
* plus I don't have time, 5 days till submission, whatever complex system I couldn't learn in this 5 days. So oh well
*/
class HitBox
{
	Box* originalBox;
	float size;

	Box* thisTickBox;

	//bool hasMultipleBoxes;
	//std::vector<Box*> originalHitBoxes; Too Complex, not for Assignment 2
	
public:
	HitBox(Box* box);
	HitBox();
	//HitBox(std::vector<Box*> boxes);
	~HitBox();

	Box* getOriginalBox();
	Box* getThisTickBox();

	//void setHitBox(std::vector<Box*> boxes);

	//This should be the Box that is defined before any scaling (Size after gen'd from MeshBuilder).
	void setOriginalHitBox(Box* box);

	//void update(EntityData*);
	void update(Mtx44 matrix); //Updates the entire hitbox's location based of the current obj Location
	//Further optimizations can be done with update, making Hitbox not get recalculated every frame if Location & size both are
	//not updated. But lack of time atm so that'll have to come in the future.

	bool collidedWith(HitBox* other);
};

