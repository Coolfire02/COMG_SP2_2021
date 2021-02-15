#include "Sonic.h"

Sonic::Sonic(Scene* associatedScene, std::string name) : Entity(associatedScene, ENTITYTYPE::SONIC, name) {
	Box* box = new Box(new Position3D(-1.5, -4.2, 1), new Position3D(1.5, 1.5, -1.5));
	this->hitBox = new HitBox(box);
	startAnimation = 0;
	speed = 1.0f;
	endAnimation = 0;
	currentAnimation = NO_ANIMATION;
	stackedAnimations = 0;
}

Sonic::~Sonic() {}

void Sonic::Update(double dt) {
	animationUpdater(dt);
}

bool Sonic::startAnAnimation(SONIC_ANIMATION animation) {
	if (currentAnimation == NO_ANIMATION) {
		//T = walk
		//G = flip

		switch (animation) {
		case WALK:
			{
				currentAnimation = SONIC_ANIMATION::WALK;
				startAnimation = this->scene->getElapsedTime();
				endAnimation = startAnimation + 2.3;
				resetAnimation();
				break;
			}
		case FLIP:
			{
				currentAnimation = SONIC_ANIMATION::FLIP;
				startAnimation = this->scene->getElapsedTime();
				endAnimation = startAnimation + 4.25;
				resetAnimation();
			break;
			}
		}

		return true;
	}
	return false;
}

void Sonic::animationUpdater(double dt) {
	double totalAnimationTime = endAnimation - startAnimation;
	double aniTime = this->scene->getElapsedTime() - startAnimation;
	//Run 1.5s
	//Walk 2s
	//RunJump 3s
	if (currentAnimation != NO_ANIMATION && aniTime >= totalAnimationTime) {
		resetAnimation();
		stackedAnimations = 0; //debug
		if (stackedAnimations > 0) {
			stackedAnimations--;
			switch (currentAnimation) { //Continuation of animation
			case WALK:
				resetAnimation();
				startAnimation = this->scene->getElapsedTime() - 0.56;
				endAnimation = startAnimation + 2.3;
			}
		}
		else {
			currentAnimation = NO_ANIMATION;
			return;
		}
	}
	switch (currentAnimation) {
	case WALK:
	{
		double animationStart;
		double animationLength;
		float degreeTilt;
		SONIC_ANIMATION_OFFSET type;
		SONIC_POSITION_OFFSET posType;

		//animationStart = 0.4;
		//animationLength = 2.3;
		//degreeTilt = 0.3f;
		//posType = SONIC_POSITION_OFFSET::OBJECTZ;
		//processDeprecatedMovement(aniTime, animationStart, animationLength, degreeTilt, posType);

		animationStart = 0.0;
		animationLength = 0.45;
		degreeTilt = 0.7f;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);


		animationStart = 0.0;
		animationLength = 0.45;
		degreeTilt = 1;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.08;
		animationLength = 0.45;
		degreeTilt = -5;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.40;
		animationLength = 0.80;
		degreeTilt = 1.2f;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.40;
		animationLength = 0.8;
		degreeTilt = 3;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.60;
		animationLength = 1.00;
		degreeTilt = 5;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.1;
		animationLength = 2.0;
		degreeTilt = -1.9f;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.1;
		animationLength = 2.0;
		degreeTilt = -5;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.7;
		degreeTilt = -3;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.95;
		animationLength = 2.3;
		degreeTilt = 2.6f;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.95;
		animationLength = 2.3;
		degreeTilt = 4;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.95;
		animationLength = 2.3;
		degreeTilt = 4;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.6;
		animationLength = 1.2;
		degreeTilt = -1.3f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.6;
		animationLength = 1.2;
		degreeTilt = 3;
		type = SONIC_ANIMATION_OFFSET::RIGHT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.70;
		animationLength = 1.2;
		degreeTilt = -2;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.8;
		degreeTilt = 2.8f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.8;
		degreeTilt = -5;
		type = SONIC_ANIMATION_OFFSET::RIGHT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.15;
		animationLength = 1.9;
		degreeTilt = 1.3f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.75;
		animationLength = 2.3;
		degreeTilt = -1.75;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 1.75;
		animationLength = 2.3;
		degreeTilt = 4;
		type = SONIC_ANIMATION_OFFSET::RIGHT_ARM_ELBOW_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);
		break;
	}

	case FLIP:
	{
		double animationStart;
		double animationLength;
		float degreeTilt;
		SONIC_ANIMATION_OFFSET type;
		SONIC_POSITION_OFFSET posType;

		//animationStart = 0.7;
		//animationLength = 4;
		//degreeTilt = 0.5;
		//posType = SONIC_POSITION_OFFSET::OBJECTZ;
		//processMovement(aniTime, animationStart, animationLength, degreeTilt, posType);

		animationStart = 0.0;
		animationLength = 0.7;
		degreeTilt = 4;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.0;
		animationLength = 0.7;
		degreeTilt = 4;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.05;
		animationLength = 0.55;
		degreeTilt = -5;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.05;
		animationLength = 0.55;
		degreeTilt = -5;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.52;
		animationLength = 0.85;
		degreeTilt = -6;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.52;
		animationLength = 0.85;
		degreeTilt = -6;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.1;
		animationLength = 0.65;
		degreeTilt = -0.5;
		type = SONIC_ANIMATION_OFFSET::BODY_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.62;
		animationLength = 0.85;
		degreeTilt = -1;
		type = SONIC_ANIMATION_OFFSET::BODY_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.1;
		animationLength = 0.85;
		degreeTilt = 1.5;
		type = SONIC_ANIMATION_OFFSET::HEAD_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.78;
		animationLength = 3.50;
		degreeTilt = 29;
		type = SONIC_ANIMATION_OFFSET::CHARACTER_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.45;
		animationLength = 3.6;
		degreeTilt = 1;
		type = SONIC_ANIMATION_OFFSET::CHARACTER_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.25;
		animationLength = 3.6;
		degreeTilt = 1.4f;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_SHOULDER_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.55;
		animationLength = 3.8;
		degreeTilt = 0.55f;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_SHOULDER_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.70;
		animationLength = 4.25;
		degreeTilt = -1.95f;
		type = SONIC_ANIMATION_OFFSET::LEFT_ARM_SHOULDER_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.25;
		animationLength = 3.6;
		degreeTilt = 1.4f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_ARM_SHOULDER_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.55;
		animationLength = 3.8;
		degreeTilt = 0.55f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_ARM_SHOULDER_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.70;
		animationLength = 4.25;
		degreeTilt = -1.95f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_ARM_SHOULDER_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.55;
		animationLength = 3.70;
		degreeTilt = 0.6f;
		type = SONIC_ANIMATION_OFFSET::CHARACTER_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.65;
		animationLength = 3.80;
		degreeTilt = 0.4f;
		type = SONIC_ANIMATION_OFFSET::CHARACTER_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.75;
		animationLength = 3.90;
		degreeTilt = 0.35f;
		type = SONIC_ANIMATION_OFFSET::CHARACTER_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.85;
		animationLength = 4.25;
		degreeTilt = 1.2f;
		type = SONIC_ANIMATION_OFFSET::CHARACTER_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);


		//After spinning
		animationStart = 3.75;
		animationLength = 3.95;
		degreeTilt = -0.59f;
		type = SONIC_ANIMATION_OFFSET::HEAD_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.79;
		animationLength = 4.00;
		degreeTilt = 0.2f;
		type = SONIC_ANIMATION_OFFSET::BODY_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.5;
		animationLength = 4.05;
		degreeTilt = -1.3f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.5;
		animationLength = 4.06;
		degreeTilt = -1.3f;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_ORIGIN_PITCH;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.5;
		animationLength = 4.05;
		degreeTilt = 2.1f;
		type = SONIC_ANIMATION_OFFSET::RIGHT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 3.5;
		animationLength = 4.05;
		degreeTilt = 2.1f;
		type = SONIC_ANIMATION_OFFSET::LEFT_LEG_KNEE_TILT;
		processAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		break;

	}
	default:
	{
		aniTime = this->scene->getElapsedTime() - floor(this->scene->getElapsedTime());
		double animationStart;
		double animationLength;
		float degreeTilt;
		SONIC_ANIMATION_OFFSET type;

		animationStart = 0.0;
		animationLength = 0.5;
		degreeTilt = -0.2f;
		type = SONIC_ANIMATION_OFFSET::HAIR_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);

		animationStart = 0.5;
		animationLength = 1.0;
		degreeTilt = 0.2f;
		type = SONIC_ANIMATION_OFFSET::HAIR_TILT;
		processDeprecatedAnimation(aniTime, animationStart, animationLength, degreeTilt, type);
	}
	}
}

void Sonic::processAnimation(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_ANIMATION_OFFSET type) {
	if (aniTime >= animationStart && aniTime <= animationLength)
		animation_offset[type] = animation_offset[type] + degreeTilt / (animationLength - animationStart);
}

void Sonic::processMovement(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_POSITION_OFFSET type) {
	if (aniTime >= animationStart && aniTime <= animationLength) {
		double toAdd = degreeTilt / (animationLength - animationStart);
		toAdd *= speed;
		switch (type) {
		case HEIGHT:
			this->getEntityData()->transY += toAdd;
			break;
		case OBJECTX:
			this->getEntityData()->transX += toAdd;
			break;
		case OBJECTZ:
			this->getEntityData()->transZ += toAdd;
			break;
		}
	}
}

void Sonic::setSpeed(float speed) {
	this->speed = speed;
}

void Sonic::processDeprecatedAnimation(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_ANIMATION_OFFSET type) {
	if (aniTime >= animationStart && aniTime <= animationLength)
		animation_offset[type] = animation_offset[type] + (aniTime - animationStart) / (animationLength - animationStart) * degreeTilt;
}

void Sonic::processDeprecatedMovement(double aniTime, double animationStart, double animationLength, float degreeTilt, SONIC_POSITION_OFFSET type) {
	if (aniTime >= animationStart && aniTime <= animationLength) {
		double toAdd = (aniTime - animationStart) / (animationLength - animationStart) * degreeTilt;
		toAdd *= speed;
		switch (type) {
		case HEIGHT:
			this->getEntityData()->transY += toAdd;
			break;
		case OBJECTX:
			this->getEntityData()->transX += toAdd;
			break;
		case OBJECTZ:
			this->getEntityData()->transZ += toAdd;
			break;
		}
	}
}

void Sonic::resetAnimation() {
	for (int i = 0; i < ANIMATION_TOTAL; i++) {
		animation_offset[i] = 0.0;
	}
}

void Sonic::Render() { //Should move to this->loadOriginTRSIntoStacknHitBox(); instead of setting up manually here
	//Main model: head
	this->scene->modelStack.PushMatrix();
		//this->scene->modelStack.Rotate(10 + animation_offset[HEAD_TILT], 1.0f, 0.0f, 0.0f);
		//@Deprecated	
		EntityData* data = (this->useNewData ? this->data : this->oldData);

		this->scene->modelStack.Translate(data->transX, data->transY, data->transZ);
		this->scene->modelStack.Rotate(-10 + (float)animation_offset[CHARACTER_TILT] + (float)animation_offset[HEAD_TILT], 1.0f, 0.0f, 0.0f);
		this->scene->modelStack.Rotate(data->rotXMag, 1.f, 0.f, 0.f);
		this->scene->modelStack.Rotate(data->rotYMag, 0.f, 1.f, 0.f);
		this->scene->modelStack.Rotate(data->rotZMag, 0.f, 0.f, 1.f);
		this->scene->modelStack.Scale(data->scaleX, data->scaleY, data->scaleZ);
		
		if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HEAD), true);

		//Do this for all Entities, after their first modelStack input
		this->hitBox->update(this->scene->modelStack.Top());

		//Body
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(10 - (float)animation_offset[BODY_TILT] - (float)animation_offset[HEAD_TILT], 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Translate(0.0f, -1.2f, 0.0); //Center of body
			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Rotate(-90, 1.0f, 0.0f, 0.0f);
				this->scene->modelStack.Translate(0.0f, 0.0f, 0.0f);
				this->scene->modelStack.Scale(0.4f, 0.5f, 0.6f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BODY_BACK_HEMISPHERE), true);
			this->scene->modelStack.PopMatrix();

			//Front of body
			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
				this->scene->modelStack.Translate(0.0f, 0.0f, 0.0f);
				this->scene->modelStack.Scale(0.4f, 0.5f, 0.6f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BODY_FRONT_BLUE_HEMISPHERE_FRUSTUM), true);

				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					this->scene->modelStack.Translate(0.0f, 0.5f, 0.0f);
					this->scene->modelStack.Scale(0.8f, 0.5f, 0.8f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BODY_FRONT_ORANGE_HEMISPHERE), true);
				this->scene->modelStack.PopMatrix();
			this->scene->modelStack.PopMatrix();
			
			//Legs
			//Right Leg
			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.2f * RIGHT, -0.4f, 0.0f);
				this->scene->modelStack.Rotate(10 * RIGHT, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Rotate((float)-animation_offset[RIGHT_LEG_ORIGIN_PITCH], 1.0f, 0.0f, 0.0f); //to go back
				this->scene->modelStack.Scale(0.12f, 0.12f, 0.12f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGHEMISPHERE), true);

				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Translate(0.f, -2.8f, 0.0f);
					this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					this->scene->modelStack.Scale(1.0, 5.6f, 1.0f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGCYLINDER), true);

					this->scene->modelStack.PushMatrix();
						this->scene->modelStack.Scale(1.0, 0.1785f, 1.0f);
						this->scene->modelStack.Translate(0.f, -2.9f, 0.0f);
						this->scene->modelStack.Rotate((float)-animation_offset[RIGHT_LEG_KNEE_TILT], 1.0f, 0.0f, 0.0f);
						if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGSPHERE), true);

						this->scene->modelStack.PushMatrix();

							this->scene->modelStack.Translate(0.f, -3.2f, 0.0f);
							this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
							this->scene->modelStack.Scale(0.85f, 5.6f, 0.85f);
							if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGCYLINDER), true);

							this->scene->modelStack.PushMatrix();
								this->scene->modelStack.Translate(0.f, -0.5f, 0.0f);
								this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								this->scene->modelStack.Scale(0.8f, 0.12f, 0.8f);
								this->scene->modelStack.Rotate(-10 * RIGHT, 0.0f, 0.0f, 1.0f);
								if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGTORUS), true);

								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Translate(0.f, -1.4f, 0.0f);
									this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(1.0f, 0.8f, 1.0f);
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGTORUS), true);

									//Front shoe
									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.4f * RIGHT, -8.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(5.0f, 8.f, 10.f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

										//Lace
										this->scene->modelStack.PushMatrix();
											this->scene->modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
											this->scene->modelStack.Translate(-0.3f, 0.0f, 0.0f);
											this->scene->modelStack.Rotate(-83, 0.0f, 0.0f, 1.0f);
											this->scene->modelStack.Scale(0.75f, 4.f, 0.8f); //x is tallness, y value is width, 
											if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSLACEHALFTORUS), true);

										this->scene->modelStack.PopMatrix();

										this->scene->modelStack.PushMatrix();
											this->scene->modelStack.Translate(0.f, -0.12f, 0.25f);
											this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
											this->scene->modelStack.Scale(0.8f, 0.8f, 0.6f);
											if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSFEETTORUS), true);
										this->scene->modelStack.PopMatrix();

									this->scene->modelStack.PopMatrix();

									//Back shoe
									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Translate(-0.4f * RIGHT, -8.0f, -0.3f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(5.0f, 8.f, 4.f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();
							this->scene->modelStack.PopMatrix();
						this->scene->modelStack.PopMatrix();
					this->scene->modelStack.PopMatrix();
				this->scene->modelStack.PopMatrix();
			this->scene->modelStack.PopMatrix();


			//Left Leg
			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.2f * LEFT, -0.4f, 0.0f);
				this->scene->modelStack.Rotate(10 * LEFT, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Rotate((float)-animation_offset[LEFT_LEG_ORIGIN_PITCH], 1.0f, 0.0f, 0.0f); //to go back
				this->scene->modelStack.Scale(0.12f, 0.12f, 0.12f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGHEMISPHERE), true);

				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Translate(0.f, -2.8f, 0.0f);
					this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					this->scene->modelStack.Scale(1.0, 5.6f, 1.0f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGCYLINDER), true);

					this->scene->modelStack.PushMatrix();
						this->scene->modelStack.Scale(1.0, 0.1785f, 1.0f);
						this->scene->modelStack.Translate(0.f, -2.9f, 0.0f);
						this->scene->modelStack.Rotate((float)-animation_offset[LEFT_LEG_KNEE_TILT], 1.0f, 0.0f, 0.0f);
						if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGSPHERE), true);

						this->scene->modelStack.PushMatrix();
							this->scene->modelStack.Translate(0.f, -3.2f, 0.0f);
							this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
							this->scene->modelStack.Scale(0.85f, 5.6f, 0.85f);
							if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGCYLINDER), true);

							this->scene->modelStack.PushMatrix();
								this->scene->modelStack.Translate(0.f, -0.5f, 0.0f);
								this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								this->scene->modelStack.Scale(0.8f, 0.12f, 0.8f);
								this->scene->modelStack.Rotate(-10 * LEFT, 0.0f, 0.0f, 1.0f);
								if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGTORUS), true);

								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Translate(0.f, -1.4f, 0.0f);
									this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(1.0f, 0.8f, 1.0f);
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_LEGTORUS), true);

									//Front shoe
									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.4f * LEFT, -8.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(5.0f, 8.f, 10.f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

										//Lace
										this->scene->modelStack.PushMatrix();
											this->scene->modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
											this->scene->modelStack.Translate(-0.3f, 0.0f, 0.0f);
											this->scene->modelStack.Rotate(-83, 0.0f, 0.0f, 1.0f);
											this->scene->modelStack.Scale(0.75f, 4.f, 0.8f); //x is tallness, y value is width, 
											if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSLACEHALFTORUS), true);

										this->scene->modelStack.PopMatrix();

										this->scene->modelStack.PushMatrix();
											this->scene->modelStack.Translate(0.f, -0.12f, 0.25f);
											this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
											this->scene->modelStack.Scale(0.8f, 0.8f, 0.6f);
											if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSFEETTORUS), true);
										this->scene->modelStack.PopMatrix();
									this->scene->modelStack.PopMatrix();

									//Back shoe
									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Translate(-0.4f * LEFT, -8.0f, -0.3f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(5.0f, 8.f, 4.f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BOOTSQUATERSPHERE), true);

									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();
							this->scene->modelStack.PopMatrix();
						this->scene->modelStack.PopMatrix();
					this->scene->modelStack.PopMatrix();
				this->scene->modelStack.PopMatrix();
			this->scene->modelStack.PopMatrix();
			

			//Arms
			//Right arm

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.42f * RIGHT, 0.2f, 0.0f);
				this->scene->modelStack.Rotate((float)animation_offset[RIGHT_ARM_SHOULDER_YAW], 0.0f, 1.0f, 0.0f);
				this->scene->modelStack.Rotate((float)animation_offset[RIGHT_ARM_SHOULDER_PITCH] - 60 , 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Rotate((float)-animation_offset[RIGHT_ARM_SHOULDER_ROLL], 0.0f, 1.0f, 0.0f);
				this->scene->modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Scale(0.08f, 0.12f, 0.08f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMHEMISPHERE), true);
				
				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Translate(0.0f, -1.0f*RIGHT, 0.0f);
					this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					this->scene->modelStack.Scale(1.0f, 2.f, 1.0f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMCYLINDER), true);

					this->scene->modelStack.PushMatrix();
						this->scene->modelStack.Translate(0.0f, -0.6f*RIGHT, 0.0f);
						this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
						this->scene->modelStack.Scale(1.0f, 0.3333f, 1.0f);
						if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMSPHERE), true);

						this->scene->modelStack.PushMatrix();
							this->scene->modelStack.Rotate(90 + (float)animation_offset[RIGHT_ARM_ELBOW_PITCH], 0.0f, 1.0f, 0.0f); //arm back and fourth
							this->scene->modelStack.Rotate(20 + (float)animation_offset[RIGHT_ARM_ELBOW_ROLL], 1.0f, 0.0f, 0.0f);
							this->scene->modelStack.Translate(0.0f, -5.5f*RIGHT, 0.0f);
							this->scene->modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f); //Make hand face body
							this->scene->modelStack.Scale(1.0f, 10.4f, 1.0f);
							if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMCYLINDER), true);
					
							//Arm Torus Outter
							this->scene->modelStack.PushMatrix();
								this->scene->modelStack.Translate(0.0f, -0.40f * RIGHT, 0.0f);
								this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								this->scene->modelStack.Scale(0.8f, 0.07f, 0.8f);
								if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDTORUS), true);

								//Arm Torus Inner
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Translate(0.0f, -0.8f * RIGHT, 0.0f);
									this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(1.0f, 0.8f, 1.0f);
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDTORUS), true);
								this->scene->modelStack.PopMatrix();
							this->scene->modelStack.PopMatrix();

							//Hand
							this->scene->modelStack.PushMatrix();
								this->scene->modelStack.Translate(-1.3f, -0.61f * RIGHT, 0.0f);
								this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
								this->scene->modelStack.Scale(0.20f, 3.f, 2.5f); //z fatter x is longer
								if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);

								//Thumb
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(-71 * RIGHT, 0.0f, 1.0f, 0.0f); //Angle of finger on the hemisphere
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.20f, 0.5f, 0.26f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();

								this->scene->modelStack.PopMatrix();

								//Index
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(-20 * RIGHT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Rotate(1, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.8f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();

								this->scene->modelStack.PopMatrix();

								//Middle
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(5 * RIGHT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Rotate(3, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.85f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();

								//Ring
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(30 * RIGHT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Rotate(2, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.75f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();

								//Pinky
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(60 * RIGHT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Translate(1.2f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.35f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();

							this->scene->modelStack.PopMatrix();
						this->scene->modelStack.PopMatrix();
					this->scene->modelStack.PopMatrix();
				this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();
		


			//Left arm

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.42f * LEFT , 0.2f, 0.0f);
				
				//this->scene->modelStack.Rotate(rotateAngle, 1.0f, 0.0f, 0.0f); //to go b
				this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip from right arm
				this->scene->modelStack.Rotate((float)animation_offset[LEFT_ARM_SHOULDER_YAW], 0.0f, 1.0f, 0.0f);
				this->scene->modelStack.Rotate((float)animation_offset[LEFT_ARM_SHOULDER_PITCH] - 60, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Rotate((float)animation_offset[LEFT_ARM_SHOULDER_ROLL], 0.0f, 1.0f, 0.0f);

				this->scene->modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Scale(0.08f, 0.12f, 0.08f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMHEMISPHERE), true);
				
				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Translate(0.0f, -1.0f, 0.0f);
					
					this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
					this->scene->modelStack.Scale(1.0f, 2.f, 1.0f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMCYLINDER), true);

					this->scene->modelStack.PushMatrix();
						
						
						this->scene->modelStack.Translate(0.0f, -0.6f, 0.0f);
						
						this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
						this->scene->modelStack.Scale(1.0f, 0.3333f, 1.0f);
						if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMSPHERE), true);

						this->scene->modelStack.PushMatrix();
							
							this->scene->modelStack.Rotate(90 + (float)animation_offset[LEFT_ARM_ELBOW_PITCH], 0.0f, 1.0f, 0.0f); //arm back and fourth
							this->scene->modelStack.Rotate(20 + (float)animation_offset[LEFT_ARM_ELBOW_ROLL], 1.0f, 0.0f, 0.0f);

							this->scene->modelStack.Translate(0.0f, -5.5f, 0.0f);
							
							this->scene->modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f); //Make hand face body

							
							this->scene->modelStack.Scale(1.0f, 10.4f, 1.0f);
							if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_ARMCYLINDER), true);
					
							//Arm Torus Outter
							this->scene->modelStack.PushMatrix();
								this->scene->modelStack.Translate(0.0f, -0.40f , 0.0f);

								this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
								this->scene->modelStack.Scale(0.8f, 0.07f, 0.8f);
								if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDTORUS), true);

								//Arm Torus Inner
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Translate(0.0f, -0.8f , 0.0f);

									this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(1.0f, 0.8f, 1.0f);
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDTORUS), true);
								this->scene->modelStack.PopMatrix();

							this->scene->modelStack.PopMatrix();

							//Hand
							this->scene->modelStack.PushMatrix();
								this->scene->modelStack.Translate(-1.3f, -0.61f , 0.0f);

								this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
								this->scene->modelStack.Scale(0.20f, 3.f, 2.5f); //z fatter x is longer
								if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);

								//Thumb
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(-71 * LEFT , 0.0f, 1.0f, 0.0f); //Angle of finger on the hemisphere
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.20f, 0.5f, 0.26f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();

								this->scene->modelStack.PopMatrix();

								//Index
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(-20 * LEFT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Rotate(1, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.8f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();

								this->scene->modelStack.PopMatrix();

								//Middle
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(5 * LEFT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Rotate(3, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.85f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();

								//Ring
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(30 * LEFT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Rotate(2, 0.0f, 0.0f, 1.0f); //Tilting upwards angle
									this->scene->modelStack.Translate(1.4f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.75f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();

								//Pinky
								this->scene->modelStack.PushMatrix();
									this->scene->modelStack.Rotate(60 * LEFT, 0.0f, 1.0f, 0.0f);
									this->scene->modelStack.Translate(1.2f, 0.3f, 0.0f);
									this->scene->modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
									this->scene->modelStack.Scale(0.15f, 0.35f, 0.22f); //y is for length
									if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDCYLINDER), true);

									this->scene->modelStack.PushMatrix();
										this->scene->modelStack.Translate(0.0f, 1.0f, 0.0f);
										this->scene->modelStack.Rotate(0, 0.0f, 0.0f, 1.0f);
										this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
										if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HANDHEMISPHERE), true);
									this->scene->modelStack.PopMatrix();
								this->scene->modelStack.PopMatrix();

							this->scene->modelStack.PopMatrix();
						this->scene->modelStack.PopMatrix();
					this->scene->modelStack.PopMatrix();
				this->scene->modelStack.PopMatrix();
			//Push out of arms
			this->scene->modelStack.PopMatrix();



		//Push out of body
		this->scene->modelStack.PopMatrix();



		//Eyes
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(10, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Translate(-0.3f, -0.15f, 0.94f);
			this->scene->modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Scale(0.135f, 0.3f, 0.135f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_EYEBALL), true);

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Rotate(-5, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Translate(0.35f, -0.4f, 0.7f);
				this->scene->modelStack.Rotate(17, 1.0f, 0.0f, 0.0f);
				this->scene->modelStack.Scale(0.3f, 0.3f, 0.3f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_GREENEYE), true);

				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Translate(0.10f, 0.0f, 0.7f);
					this->scene->modelStack.Rotate(0, 1.0f, 1.0f, 1.0f);
					this->scene->modelStack.Scale(0.7f, 0.58f, 0.7f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BLACKEYE), true);
				
					this->scene->modelStack.PopMatrix();
			this->scene->modelStack.PopMatrix();
		this->scene->modelStack.PopMatrix();
		
		//Eyes 2
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(-10, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Translate(0.3f, -0.15f, 0.94f);
			this->scene->modelStack.Rotate(10, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Scale(0.135f, 0.3f, 0.135f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_EYEBALL), true);

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Rotate(-5, 0.0f, 1.0f, 0.0f);
				this->scene->modelStack.Translate(-0.35f, -0.4f, 0.7f);
				this->scene->modelStack.Rotate(-17, 0.0f, 1.0f, 0.0f);
				this->scene->modelStack.Rotate(17, 1.0f, 0.0f, 0.0f);
				this->scene->modelStack.Scale(0.3f, 0.3f, 0.3f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_GREENEYE), true);

				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Translate(0.10f, 0.0f, 0.7f);
					this->scene->modelStack.Rotate(0, 1.0f, 1.0f, 1.0f);
					this->scene->modelStack.Scale(0.7f, 0.58f, 0.7f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_BLACKEYE), true);

				this->scene->modelStack.PopMatrix();
			this->scene->modelStack.PopMatrix();
		this->scene->modelStack.PopMatrix();

		//Ears 1
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.55f, 0.8f, 0.3f);
			this->scene->modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(-27, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Rotate(-5, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Scale(0.55f, 0.55f, 0.75f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_EARS), true);

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.0f, 0.0f, 0.06f);
				this->scene->modelStack.Scale(0.8f, 0.8f, 0.8f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_INNERSONICEARS), true);

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();


		//Ears 2
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(-0.55f, 0.8f, 0.3f);
			this->scene->modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(27, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Rotate(5, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Scale(0.55f, 0.55f, 0.75f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_EARS), true);

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.0f, 0.0f, 0.06f);
				this->scene->modelStack.Scale(0.8f, 0.8f, 0.8f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_INNERSONICEARS), true);

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		//Mouth
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(10, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Translate(0.0f, -0.4f, 0.1f);
			this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(1.4f, 0.55f, 1.4f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_MOUTHTORUS), true);

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.0f, 0.0f, 0.53f);	
				//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f);
				this->scene->modelStack.Scale(0.2f, 0.3f, 0.08f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_MOUTHSPHERE), true);

				//this->scene->modelStack.PushMatrix();
				//	this->scene->modelStack.Rotate(-20, 1.0f, 0.0f, 0.0f);
				//	this->scene->modelStack.Translate(0.0f, 0.2f, 1.3f);
				//	this->scene->modelStack.Rotate(-6, 1.0f, 0.0f, 0.0f);
				//	//this->scene->modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
				//	this->scene->modelStack.Scale(0.15f, 0.3f, 0.8f);
				//	if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_NOSESPHERE), true);
				//this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		


		//Hair 1 (top left hair)
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f); //turn to left side
			this->scene->modelStack.Translate(0.7f, 0.4f, -0.7f);
			//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Rotate(20 + (float)animation_offset[HAIR_TILT], 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//this->scene->modelStack.Scale(0.45f, 1.4f, 0.65f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

			this->scene->modelStack.PushMatrix();
				this->scene->modelStack.Translate(0.f, 0.0f, 0.0f);
				this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
				this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
				if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

				
					
				this->scene->modelStack.Translate(0.f, 0.0f, -0.75f);
				this->scene->modelStack.Scale(0.6f, 1.0f, 0.3f);
				//this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
				this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
					
					

				this->scene->modelStack.PushMatrix();
					this->scene->modelStack.Scale(0.6f, 0.8f, 0.5f);
					this->scene->modelStack.Translate(0.f, 0.3f, -0.8f);

					this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
					this->scene->modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
					this->scene->modelStack.Scale(1.0f, 1.0f, 1.0f);
					if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHEREFRUSTUM), true);

					this->scene->modelStack.PushMatrix();
						this->scene->modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

						this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
						this->scene->modelStack.Scale(0.8f, 0.5f, 0.5f);
						if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


						this->scene->modelStack.PopMatrix();

					this->scene->modelStack.PushMatrix();
					//this->scene->modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

					//this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
					//this->scene->modelStack.Scale(1.f, 1.0f, 1.0f);

						this->scene->modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
						this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
						this->scene->modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
						this->scene->modelStack.Scale(0.8f, 0.5f, 1.0f);
						if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


					this->scene->modelStack.PopMatrix();

				this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		//Hair 2 (top right hair)
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(10, 0.0f, 1.0f, 0.0f); //turn to left side
			this->scene->modelStack.Translate(-0.7f, 0.4f, -0.7f);
			//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Rotate(20 + (float)animation_offset[HAIR_TILT], 1.0f, 0.0f, 0.0f); //slant to left side
			this->scene->modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//this->scene->modelStack.Scale(0.45f, 1.4f, 0.65f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);



			this->scene->modelStack.Translate(0.f, 0.0f, -0.75f);
			this->scene->modelStack.Scale(0.6f, 1.0f, 0.3f);
			//this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Scale(0.6f, 0.8f, 0.5f);
			this->scene->modelStack.Translate(0.f, 0.3f, -0.8f);

			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(1.0f, 1.0f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHEREFRUSTUM), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 0.5f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PushMatrix();
			//this->scene->modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//this->scene->modelStack.Scale(1.f, 1.0f, 1.0f);

			this->scene->modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			this->scene->modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		//Hair 3 (top hair)
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(15, 1.0f, 0.0f, 0.0f); //turn to up side
			this->scene->modelStack.Translate(0.0f, 0.6f, -0.7f);
			//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Rotate(20 + (float)animation_offset[HAIR_TILT], 1.0f, 0.0f, 0.0f); //slant to left side
			this->scene->modelStack.Scale(0.3525f, 0.5025f, 1.1f);
			//this->scene->modelStack.Scale(0.45f, 1.4f, 0.65f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);



			this->scene->modelStack.Translate(0.f, 0.0f, -0.75f);
			this->scene->modelStack.Scale(0.6f, 1.0f, 0.3f);
			//this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Scale(0.6f, 0.8f, 0.5f);
			this->scene->modelStack.Translate(0.f, 0.3f, -0.8f);

			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(1.0f, 1.0f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHEREFRUSTUM), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 0.5f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PushMatrix();
			//this->scene->modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//this->scene->modelStack.Scale(1.f, 1.0f, 1.0f);

			this->scene->modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			this->scene->modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		//Hair 4 (Middle hair)
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(-15 + (float)animation_offset[HAIR_TILT], 1.0f, 0.0f, 0.0f); //turn to down side
			this->scene->modelStack.Translate(0.0f, 0.3f, -0.7f);
			//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			this->scene->modelStack.Scale(0.3525f, 0.5025f, 1.1f);
			//this->scene->modelStack.Scale(0.45f, 1.4f, 0.65f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);



			this->scene->modelStack.Translate(0.f, 0.0f, -0.75f);
			this->scene->modelStack.Scale(0.6f, 1.0f, 0.3f);
			//this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Scale(0.6f, 0.8f, 0.5f);
			this->scene->modelStack.Translate(0.f, 0.3f, -0.8f);

			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(1.0f, 1.0f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHEREFRUSTUM), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 0.5f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PushMatrix();
			//this->scene->modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//this->scene->modelStack.Scale(1.f, 1.0f, 1.0f);

			this->scene->modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			this->scene->modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		//Hair 5 (bottom left hair)
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(-10, 0.0f, 1.0f, 0.0f); //turn to left side
			this->scene->modelStack.Rotate(-25 + (float)animation_offset[HAIR_TILT], 1.0f, 0.0f, 0.0f); //turn to down side
			this->scene->modelStack.Translate(0.55f, 0.0f, -0.7f);
			//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			this->scene->modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//this->scene->modelStack.Scale(0.45f, 1.4f, 0.65f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);



			this->scene->modelStack.Translate(0.f, 0.0f, -0.75f);
			this->scene->modelStack.Scale(0.6f, 1.0f, 0.3f);
			//this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Scale(0.6f, 0.8f, 0.5f);
			this->scene->modelStack.Translate(0.f, 0.3f, -0.8f);

			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(1.0f, 1.0f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHEREFRUSTUM), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 0.5f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PushMatrix();
			//this->scene->modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//this->scene->modelStack.Scale(1.f, 1.0f, 1.0f);

			this->scene->modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			this->scene->modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

		//Hair 6 (bottom right hair)
		this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Rotate(10, 0.0f, 1.0f, 0.0f); //turn to left side
			this->scene->modelStack.Rotate(-25 + (float)animation_offset[HAIR_TILT], 1.0f, 0.0f, 0.0f); //turn to down side
			this->scene->modelStack.Translate(-0.55f, 0.0f, -0.7f);
			//this->scene->modelStack.Rotate(30, 1.0f, 0.0f, 0.0f); //look upwards
			this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f); //slant to left side
			this->scene->modelStack.Scale(0.3825f, 0.5525f, 1.19f);
			//this->scene->modelStack.Scale(0.45f, 1.4f, 0.65f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);
			this->scene->modelStack.Scale(1.0f, 0.3f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHERE), true);



			this->scene->modelStack.Translate(0.f, 0.0f, -0.75f);
			this->scene->modelStack.Scale(0.6f, 1.0f, 0.3f);
			//this->scene->modelStack.Rotate(20, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Rotate(180, 0.0f, 0.0f, 1.0f);



			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Scale(0.6f, 0.8f, 0.5f);
			this->scene->modelStack.Translate(0.f, 0.3f, -0.8f);

			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
			this->scene->modelStack.Rotate(90 + 15, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(1.0f, 1.0f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHEMISPHEREFRUSTUM), true);

			this->scene->modelStack.PushMatrix();
			this->scene->modelStack.Translate(0.0f, 1.1f, 0.2f); //1.1move front 0.2 movedown

			this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 0.5f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PushMatrix();
			//this->scene->modelStack.Translate(0.0f, 0.0f, -0.1f); //-0.5 moveup

			//this->scene->modelStack.Rotate(5, 1.0f, 0.0f, 0.0f); //tilt down
			//this->scene->modelStack.Scale(1.f, 1.0f, 1.0f);

			this->scene->modelStack.Translate(0.0f, 1.1f, 0.25f); //1.1move front -0.2 moveup
			this->scene->modelStack.Rotate(180, 0.0f, 1.0f, 0.0f); //flip
			this->scene->modelStack.Rotate(-2, 1.0f, 0.0f, 0.0f);
			this->scene->modelStack.Scale(0.8f, 0.5f, 1.0f);
			if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(GEO_SONIC_HAIRHALFCONE), true);


			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

			this->scene->modelStack.PopMatrix();

		this->scene->modelStack.PopMatrix();

	this->scene->modelStack.PopMatrix();
}