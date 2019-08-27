#pragma once
#include "Actor.h"
#include "AnimSpriteComponent.h"
#include <iostream> 
#include <time.h>
class Character :
	public Actor
{
public:
	Character(class Game*game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
	void PlayAnim(const char* animName);
	void Sleep(float s);
private:
	float mRightSpeed;
	float mDownSpeed;
	class AnimSpriteComponent* asc ;
	std::map<const char*, std::vector<SDL_Texture*>> animations;
};

