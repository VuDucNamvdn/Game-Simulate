#include "Character.h"
#include "Game.h"


Character::Character(Game* game): Actor(game), mRightSpeed(0.0f)
, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> Idle = {
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
	animations.emplace("Idle", Idle);
	animations.emplace("Jump", Jump);
	animations.emplace("Punch", Punch);

	asc->SetAnimTextures(Idle);
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
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
	

}

void Character::ProcessKeyboard(const uint8_t * state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;

	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		PlayAnim("Jump");
	}
	else if (state[SDL_SCANCODE_T])
	{
		PlayAnim("Punch");
	}
	else
	{
		PlayAnim("Idle");
	}
	
}

void Character::PlayAnim(const char * animName)
{
	asc->SetAnimTextures(animations[animName]);
}


