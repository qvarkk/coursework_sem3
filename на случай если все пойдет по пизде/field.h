#ifndef FIELD_H
#define FIELD_H

#include "tile.h"

class Field {
	private:
		int sizeX, sizeY;
		Tile **tiles;
	public:
		Field(int, int);
		~Field();
		void SetSize(int, int);
		std::vector<int> GetSize();
		Tile GetTile(int, int);
};


#endif