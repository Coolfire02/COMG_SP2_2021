#include "HitBox.h"

HitBox::HitBox(Box* box) : size(1.0f), originalBox(box), thisTickBox(nullptr) {
	/*this->originalHitBoxes.push_back(box);
	hasMultipleBoxes = false;*/
}

HitBox::HitBox() : size(1.0f), originalBox(nullptr), thisTickBox(nullptr) {

}

void HitBox::setOriginalHitBox(Box* box) {
	originalBox = box;
}

bool HitBox::collidedWith(HitBox* other) {
	if (this->thisTickBox != nullptr && other->getThisTickBox() != nullptr) {
		if (this->thisTickBox->locIsInBox(other->getThisTickBox()))
			return true;
	}
	return false;
}

Box* HitBox::getOriginalBox() {
	return this->originalBox;
}

Box* HitBox::getThisTickBox() {
	return this->thisTickBox;
}

//HitBox::HitBox(std::vector<Box*> boxes) : size(1.0f) {
//	this->originalHitBoxes = boxes;
//	hasMultipleBoxes = true;
//}

//void HitBox::setHitBox(std::vector<Box*> boxes) {
//	this->originalHitBoxes = boxes;
//}

void HitBox::update(Mtx44 matrix) {
	//Asking for MTX 44 Input old function:
	//Needed to flip axis if any axis > 90. Sticking with only reading T and S, skipping R for now

	Mtx44 bot = Mtx44(originalBox->botLeftPos->getX(), originalBox->botLeftPos->getY(), originalBox->botLeftPos->getZ(), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Mtx44 top = Mtx44(originalBox->topRightPos->getX(), originalBox->topRightPos->getY(), originalBox->topRightPos->getZ(), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if (thisTickBox == nullptr) thisTickBox = new Box(new Position3D(this->originalBox->botLeftPos), new Position3D(this->originalBox->topRightPos));

	//Attempting to fix inverted hitboxes
	//float lowX, lowY, lowZ,
	//	highX, highY, highZ;
	//lowX = lowY = lowZ = highX = highY = highZ = 0.0f;

	//lowX = Math::Min(bot.ValueAtPos(0, 0), top.ValueAtPos(0, 0));
	//highX = Math::Max(bot.ValueAtPos(0, 0), top.ValueAtPos(0, 0));

	//lowY = Math::Min(bot.ValueAtPos(1, 0), top.ValueAtPos(1, 0));
	//highY = Math::Max(bot.ValueAtPos(1, 0), top.ValueAtPos(1, 0));

	//lowZ = Math::Min(bot.ValueAtPos(0, 0), top.ValueAtPos(0, 0));
	//highZ = Math::Max(bot.ValueAtPos(0, 0), top.ValueAtPos(0, 0));


	bot = matrix * bot;
	thisTickBox->botLeftPos->setX(bot.ValueAtPos(0, 0));
	thisTickBox->botLeftPos->setY(bot.ValueAtPos(1, 0));
	thisTickBox->botLeftPos->setZ(bot.ValueAtPos(2, 0));

	top = matrix * top;
	thisTickBox->topRightPos->setX(top.ValueAtPos(0, 0));
	thisTickBox->topRightPos->setY(top.ValueAtPos(1, 0));
	thisTickBox->topRightPos->setZ(top.ValueAtPos(2, 0));
}

HitBox::~HitBox() {
	delete originalBox;
	delete thisTickBox;
}