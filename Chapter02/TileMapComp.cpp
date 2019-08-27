#include "TileMapComp.h"




TileMapComp::TileMapComp(Actor * owner, int drawOrder):SpriteComponent(owner)
{
}

void TileMapComp::parseCSV(std::string path,int sizeX,int SizeY)
{
	std::ifstream file("sheet.csv");

	for (int row = 0; row < 24; ++row)
	{
		std::string line;
		std::getline(file, line);
		if (!file.good())
			break;

		std::stringstream iss(line);

		for (int col = 0; col < 32; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');
			if (!iss.good())
				break;

			std::stringstream convertor(val);
			convertor >> tile[row][col];
		}
	}
}

void TileMapComp::AddTile(int id, int x, int y)
{

}

void TileMapComp::Draw(SDL_Renderer * renderer)
{

}


