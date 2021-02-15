#pragma once
#include "Entity.h"

enum SONIC_DIRECTION {
	LEFT = -1,
	RIGHT = 1,
};

enum SONIC_ANIMATION {
	WALK,
	FLIP,
	HAIR,
	NO_ANIMATION,
};

enum SONIC_POSITION_OFFSET {
	HEIGHT,
	OBJECTX,
	OBJECTZ,
	POSITIONTYPE_TOTAL
};

enum SONIC_ANIMATION_OFFSET {
	BODY_TILT = 0,
	CHARACTER_TILT,
	HEAD_TILT,
	HAIR_TILT,

	LEFT_ARM_ELBOW_PITCH,
	LEFT_ARM_ELBOW_ROLL,
	LEFT_ARM_SHOULDER_YAW,
	LEFT_ARM_SHOULDER_PITCH,
	LEFT_ARM_SHOULDER_ROLL,

	RIGHT_ARM_ELBOW_PITCH,
	RIGHT_ARM_ELBOW_ROLL,
	RIGHT_ARM_SHOULDER_YAW,
	RIGHT_ARM_SHOULDER_PITCH,
	RIGHT_ARM_SHOULDER_ROLL,

	LEFT_LEG_ORIGIN_PITCH,
	RIGHT_LEG_ORIGIN_PITCH,

	LEFT_LEG_KNEE_TILT,
	RIGHT_LEG_KNEE_TILT,

	ANIMATION_TOTAL
};

class Sonic: public Entity
{
	double animation_offset[ANIMATION_TOTAL];
	double position_offset[POSITIONTYPE_TOTAL];

	//Animation
	double startAnimation;
	double endAnimation;
	int stackedAnimations;
	SONIC_ANIMATION currentAnimation;

	float speed;
	

	void animationUpdater(double dt); //To be called in update
	void resetAnimation();
	void processAnimation(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_ANIMATION_OFFSET type);
	void processMovement(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_POSITION_OFFSET type);
	void processDeprecatedAnimation(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_ANIMATION_OFFSET type);
	void processDeprecatedMovement(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_POSITION_OFFSET type);


public:
	bool startAnAnimation(SONIC_ANIMATION);
	void setSpeed(float speed);
	Sonic(Scene*, std::string);
	~Sonic();
	void Update(double);
	void Render();
};

