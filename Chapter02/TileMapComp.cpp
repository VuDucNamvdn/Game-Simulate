#include "TileMapComp.h"




TileMapComp::TileMapComp(Actor * owner, float scrolls):SpriteComponent(owner)
{
	scroll = scrolls;

	scrolling = scrolls - 992.0f;
	
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



void TileMapComp::render(SDL_Texture* mTexture)
{
	gTex = mTexture;
	if (!gTex)
	{
		printf("Failed to load tile set texture Tiles!\n");
		return;
	}

}

void TileMapComp::Draw(SDL_Renderer * renderer)
{
	SDL_Rect map;
	for (int row = 0; row < 24; ++row)
	{
		for (int col = 0; col < 32; ++col)
		{
			scrolling -= 0.01f;
			if (scroll < 2976)
			{
				if (scrolling <= -2976 + scroll)
				{
					scrolling = scroll;
				}
			}
			else
			{
				if (scrolling <= -3968 + scroll)
				{
					scrolling = scroll - 992;
				}
			}
			int k = 32;
			//Set rendering space and render to screen
			SDL_Rect renderQuad = { (float)(col*k + scrolling), row*k, k, k };

			map.w = 32;
			map.h = 32;
			if (tile[row][col] != -1)
			{
				map.x = (tile[row][col] % 8) * 32;
				map.y = (tile[row][col] / 8) * 32;
				//Render to screen
				SDL_RenderCopyEx(renderer, gTex, &map, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
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


