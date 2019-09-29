#include "Pros.h"
#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Ship.h"
Pros::Pros(Game * game, Spawn State) :Actor(game), mDeathTimer(2.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	SetSpawn(State);
	SetScale(.2f);
	switch (State)
	{
	case Actor::EA:
		sc->SetTexture(game->GetTexture("Assets/ALaser.png"));
		break;
	case Actor::ES:
		sc->SetTexture(game->GetTexture("Assets/SLaser.png"));
		break;
	case Actor::Gold:
		sc->SetTexture(game->GetTexture("Assets/Gold.png"));
		break;
	default:
		break;
	}

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);
}
void Pros::UpdateActor(float deltaTime)
{
	auto mShip = GetGame()->GetShip();
	
	if (Intersect(*mCircle, *(mShip->GetCircle())))
	{
		if (GetSpawn()!=Gold)
		{
			mShip->SetSpawn(GetSpawn());
		}
		else    
		{
			GetGame()->score += 100;
		}
		SetState(EDead);
	}
}