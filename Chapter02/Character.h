#pragma once
#include "Actor.h"
#include <iostream> 
class Character :
	public Actor
{
public:
	Character(class Game*game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
	class AnimSpriteComponent* asc ;
	bool bIsJump;
};

