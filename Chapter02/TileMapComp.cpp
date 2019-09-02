#include "TileMapComp.h"




TileMapComp::TileMapComp(Actor * owner):SpriteComponent(owner)
{

}

void TileMapComp::parseCSV(std::string path)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cout << "cannot open file csv" << std::endl;
		return;
	}
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



void TileMapComp::render(SDL_Texture* mTexture,SDL_Renderer * ren)
{
	SDL_Rect map;
	if (!mTexture)
	{
		printf("Failed to load tile set texture Tiles!\n");
		return;
	}
	for (int row = 0; row < 24; ++row)
	{
		for (int col = 0; col < 32; ++col)
		{
			//Set rendering space and render to screen
			SDL_Rect renderQuad = { row*64, col*64, 64, 64 };

			map.w = 32;
			map.h = 32;
			//Set clip rendering dimensions
			if (&map != NULL)
			{
				renderQuad.w = 2*map.w;
				renderQuad.h = 2*map.h;
			}
			if (tile[row][col]>0)
			{
				map.x = tile[row][col];
				map.y = col*32;
				//Render to screen
				SDL_RenderCopyEx(ren, mTexture, &map, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
			}

			
		}
	}


}

int TileMapComp::getType()
{
	return mType;
}

SDL_Rect TileMapComp::getBox()
{
	return mBox;
}


