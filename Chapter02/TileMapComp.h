#pragma once
#include "SpriteComponent.h"
#include "Game.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
class TileMapComp :public SpriteComponent
{
public:
	TileMapComp(class Actor* owner, float scrolls);
	void parseCSV(std::string path);
private:
	int tile[24][32];
	std::vector<std::vector<std::string> > parsedCsv;
	SDL_Texture* mTexture;
public:

	//Shows the tile
	void render(SDL_Texture* mTexture);
	//draw
	void Draw(SDL_Renderer* renderer) override;
	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();
	float scroll;

private:
	//The attributes of the tile
	SDL_Rect mBox;
	SDL_Texture* gTex;
	float scrolling=0;
	//The tile type
	int mType;
};

