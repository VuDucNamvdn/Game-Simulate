// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Pros.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.0f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	// Do we intersect with an asteroid?
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			// The first asteroid we intersect with,
			// set ourselves and the asteroid to dead
			SetScale(GetScale()-0.1f);
			
			if (GetScale()<=0.2f)
			{
				SetState(EDead);
			}
			ast->SetState(EDead);
			break;
		}
	}
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		
		if (GetSpawn()==EA)
		{
			Laser* lasers = new Laser(GetGame());
			lasers->SetPosition(GetPosition());
			lasers->SetRotation(GetRotation());
		}
		else if (GetSpawn()==ES)
		{
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition());
			laser->SetRotation(GetRotation());

			Laser* laser2 = new Laser(GetGame());
			laser2->SetPosition(GetPosition());
			laser2->SetRotation(GetRotation() - 1);

			Laser* laser3 = new Laser(GetGame());
			laser3->SetPosition(GetPosition());
			laser3->SetRotation(GetRotation() - 0.5);

			Laser* laser4 = new Laser(GetGame());
			laser4->SetPosition(GetPosition());
			laser4->SetRotation(GetRotation() + 1);

			Laser* laser5 = new Laser(GetGame());
			laser5->SetPosition(GetPosition());
			laser5->SetRotation(GetRotation() + 0.5);
		}
		else
		{
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition());
			laser->SetRotation(GetRotation());
		}
		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}
}
