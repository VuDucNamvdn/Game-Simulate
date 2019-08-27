#pragma once
#include "SpriteComponent.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
class TileMapComp :
	public SpriteComponent
{
public:
	TileMapComp();
	void parseCSV(std::string path, int sizeX, int SizeY);
	static void AddTile(int id, int x, int y);
	void Draw(SDL_Renderer* renderer) override;
private:
	int tile[24][32];
	std::vector<std::vector<std::string> > parsedCsv;
	SDL_Texture* mTexture;

};

