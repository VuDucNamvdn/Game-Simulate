#include "Character.h"
#include "AnimSpriteComponent.h"
#include "Game.h"


Character::Character(Game* game): Actor(game), mRightSpeed(0.0f)
, mDownSpeed(0.0f)
{
	bIsJump = false;
	// Create an animated sprite component
	asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> Idle = {
		game->GetTexture("Assets/Character01.png"),
	};
	std::vector<SDL_Texture*> Walk = {
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
	};
	std::vector<SDL_Texture*> Jump = {
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
	};
	std::vector<SDL_Texture*> Punch = {
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png"),
	};
	asc->animations.emplace("Idle", Idle);
	asc->animations.emplace("Walk", Walk);
	asc->animations.emplace("Jump", Jump);
	asc->animations.emplace("Punch", Punch);

	asc->PlayAnim("Idle");
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 990.0f;
	}
	else if (pos.x > 1024.0f)
	{
		pos.x = 25.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 743.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 25.0f;
	}
	SetPosition(pos);
	

}

void Character::ProcessKeyboard(const uint8_t * state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_RIGHT])
	{
		mRightSpeed += 250.0f;

		asc->flip = SDL_FLIP_NONE;


	}
	if (state[SDL_SCANCODE_LEFT])
	{
		mRightSpeed -= 250.0f;

		asc->flip = SDL_FLIP_HORIZONTAL;
	}
	// up/down
	if (state[SDL_SCANCODE_DOWN])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_UP])
	{
		mDownSpeed -= 300.0f;
	}
	if (!state[SDL_SCANCODE_SPACE])
	{
		bIsJump = false;
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		if (!bIsJump)
		{
			asc->PlayAnim("Jump");
			bIsJump = true;
		}
	}
	else if (state[SDL_SCANCODE_T])
	{
		asc->PlayAnim("Punch");
	}
	else if (state[SDL_SCANCODE_RIGHT]|| state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
	{
		asc->PlayAnim("Walk");
	}
	else
	{
		asc->PlayAnim("Idle");
	}
	
}



