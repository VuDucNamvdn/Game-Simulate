// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <iostream>

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Close();
	//SDL_Log("Do you wanna play again?\n1.Yes\n2.No");
	//char n;
	//std::cin >> n;
	//switch (n)
	//{
	//case 1:
	//	game.mIsRunning = true;
	//	main(argc, argv);
	//default:
	//	game.Shutdown();
	//}
	game.Shutdown();
	return 0;
}
