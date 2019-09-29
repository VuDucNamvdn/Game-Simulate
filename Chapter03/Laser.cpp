// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Pros.h"
#include "Random.h"
Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.0f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	// Create a move component, and set a forward speed
	mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	// If we run out of time, laser is dead
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		// Do we intersect with an asteroid?
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				int random = Random::GetIntRange(0, 5);
				if (random==5)
				{
					Pros *pro = new Pros(GetGame(), ES);
					pro->SetPosition(GetPosition());
				}
				else if (random == 1)
				{
					Pros *pro = new Pros(GetGame(), EA);
					pro->SetPosition(GetPosition());
				}
				else if (random == 2)
				{
					Pros *pro = new Pros(GetGame(), Gold);
					pro->SetPosition(GetPosition());
				}
				// The first asteroid we intersect with,
				// set ourselves and the asteroid to dead
				SetState(EDead);
				ast->SetState(EDead);
				
				GetGame()->score += 10;
				break;
			}
		}
	}
}
