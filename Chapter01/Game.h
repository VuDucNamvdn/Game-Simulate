// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
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
	void RandomVel(Vector2 &Vel,float driff);
	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	//Score Board
	int score_P1 = 0;
	int score_P2 = 0;
	std::string theScore_P1;
	std::string theScore_P2;
	SDL_Rect Score_board;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Pong specific
	// Direction of paddle
	int mPaddleDir_P1;
	int mPaddleDir_P2;
	// Position of paddle
	Vector2 mPaddleP1Pos;
	// Position of paddle
	Vector2 mPaddleP2Pos;
	//surface to render score
	SDL_Surface * surface;
	SDL_Texture * texture;
	//Draw Balls
	void DrawCircle(SDL_Renderer * renderer, int32_t centerX, int32_t centerY, int32_t radius);

	TTF_Font * font;
	SDL_Color color;
	const int thickness = 15;
	const float paddleH = 100.0f;
	const int width = 1024;
	const int height = 608;
	std::vector<Ball> Balls{
		{{(float)width / 2.0f,(float)height / 2.0f},
		{-200.0f,235.0f}},
		{{(float)width / 2.0f,(float)height / 2.0f},
		{-200.0f,235.0f}},
		{{(float)width / 2.0f,(float)height / 2.0f},
		{-200.0f,235.0f}},
		{{(float)width / 2.0f,(float)height / 2.0f},
		{-200.0f,235.0f}}
	};
};
