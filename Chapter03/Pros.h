#pragma once
#include "Actor.h"
class Pros :
	public Actor
{
public:
	Pros(class Game* game,Spawn State);
	class CircleComponent* mCircle;
	float mDeathTimer;
	class CircleComponent* GetCircle() { return mCircle; }
	void UpdateActor(float deltaTime) override;
};

