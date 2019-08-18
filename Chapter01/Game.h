// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <vector>
// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

//Ball
struct Ball
{
	Vector2 Pos;
	Vector2 Vel;
};

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
	void Close();
	// Game should continue to run
	bool mIsRunning;
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;

	// Number of ticks since start of game
	Uint32 mTicksCount;
	std::vector<Ball> Balls{
		{{1024.0f / 2.0f,768.0f / 2.0f},
		{-200.0f,235.0f}},
		{{1000.0f / 2.0f,700.0f / 2.0f},
		{-200.0f,-235.0f}},
		{{926.0f / 2.0f,766.0f / 2.0f},
		{200.0f,-235.0f}}
	};
	// Pong specific
	// Direction of paddle
	int mPaddleDir_P1;
	int mPaddleDir_P2;
	// Position of paddle
	Vector2 mPaddleP1Pos;
	// Position of paddle
	Vector2 mPaddleP2Pos;
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;
	const int thickness = 15;
	const float paddleH = 100.0f;
};
