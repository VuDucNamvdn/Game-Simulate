#include "TileMapComp.h"


void TileMapComp::parseCSV(std::string path,int sizeX,int SizeY)
{
	std::ifstream  data(path);
	std::string line;
	while (std::getline(data, line))
	{
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::string> parsedRow;
		while (std::getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}

		parsedCsv.push_back(parsedRow);
	}
}

void TileMapComp::AddTile(int id, int x, int y)
{

}

void TileMapComp::Draw(SDL_Renderer * renderer)
{
}
