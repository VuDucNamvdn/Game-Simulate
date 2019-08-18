// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"



Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mPaddleDir_P1(0)
{
	
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Ping Pong", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//
	mPaddleP1Pos.x = 10.0f;
	mPaddleP1Pos.y = 768.0f/2.0f;
	mPaddleP2Pos.x = 999.0f;
	mPaddleP2Pos.y = 768.0f / 2.0f;
	//Balls[i].Pos.x = 1024.0f/2.0f;
	//Balls[i].Pos.y = 768.0f/2.0f;
	//Balls[i].Vel.x = -200.0f;
	//Balls[i].Vel.y = 235.0f;
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	mPaddleDir_P1 = 0;
	mPaddleDir_P2 = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir_P1 -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir_P1 += 1;
	}
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir_P2 -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddleDir_P2 += 1;
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle position based on direction
	if (mPaddleDir_P1 != 0)
	{
		mPaddleP1Pos.y += mPaddleDir_P1 * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddleP1Pos.y < (paddleH/2.0f + thickness))
		{
			mPaddleP1Pos.y = paddleH/2.0f + thickness;
		}
		else if (mPaddleP1Pos.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddleP1Pos.y = 768.0f - paddleH/2.0f - thickness;
		}
	}
	if (mPaddleDir_P2 != 0)
	{
		mPaddleP2Pos.y += mPaddleDir_P2 * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddleP2Pos.y < (paddleH / 2.0f + thickness))
		{
			mPaddleP2Pos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddleP2Pos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddleP2Pos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
	for (int i = 0; i < Balls.size(); i++)
	{
		// Update ball position based on ball velocity
		Balls[i].Pos.x += Balls[i].Vel.x * deltaTime;
		Balls[i].Pos.y += Balls[i].Vel.y * deltaTime;

		// Bounce if needed
		// Did we intersect with the paddles?
		float diff_1 = mPaddleP1Pos.y - Balls[i].Pos.y;
		float diff_2 = mPaddleP2Pos.y - Balls[i].Pos.y;
		// Take absolute value of difference
		diff_1 = (diff_1 > 0.0f) ? diff_1 : -diff_1;
		diff_2 = (diff_2 > 0.0f) ? diff_2 : -diff_2;
		if (
			// Our y-difference is small enough
			diff_1 <= paddleH / 2.0f &&
			// We are in the correct x-position
			Balls[i].Pos.x <= 25.0f && Balls[i].Pos.x >= 20.0f &&
			// The ball is moving to the left
			Balls[i].Vel.x < 0.0f)
		{
			Balls[i].Vel.x *= -1.0f;
		}
		// Did the ball go off the screen? (if so, end game)
		else if (Balls[i].Pos.x <= 0.0f || Balls[i].Pos.x >= 1024.0f)
		{
			mIsRunning = false;
		}
		// Did the ball collide with the right wall?
		else if (// Our y-difference is small enough
			diff_2 <= paddleH / 2.0f &&
			// We are in the correct x-position
			Balls[i].Pos.x <= 992.0f && Balls[i].Pos.x >= 984.0f &&
			// The ball is moving to the left
			Balls[i].Vel.x > 0.0f)
		{
			Balls[i].Vel.x *= -1.0f;
		}

		// Did the ball collide with the top wall?
		if (Balls[i].Pos.y <= thickness && Balls[i].Vel.y < 0.0f)
		{
			Balls[i].Vel.y *= -1;
		}
		// Did the ball collide with the bottom wall?
		else if (Balls[i].Pos.y >= (768 - thickness) &&
			Balls[i].Vel.y > 0.0f)
		{
			Balls[i].Vel.y *= -1;
		}
	}
	
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		155,	// R
		0,		// G 
		0,		// B
		100		// A
	);
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw right wall
	//wall.x = 1024 - thickness;
	//wall.y = 0;
	//wall.w = thickness;
	//wall.h = 1024;
	//SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	SDL_Rect paddle_P1{
		static_cast<int>(mPaddleP1Pos.x),
		static_cast<int>(mPaddleP1Pos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle_P1);
	SDL_Rect paddle_P2{
		static_cast<int>(mPaddleP2Pos.x),
		static_cast<int>(mPaddleP2Pos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle_P2);
	// Draw ball
	for (int i = 0; i < Balls.size(); i++)
	{
	SDL_Rect ball{	
		static_cast<int>(Balls[i].Pos.x - thickness/2),
		static_cast<int>(Balls[i].Pos.y - thickness/2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	}

	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Close()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void Game::Shutdown()
{
	SDL_Quit();
}
