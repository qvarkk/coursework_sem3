#ifndef FIELD_H
#define FIELD_H

#include "tile.h"

class Field {
	private:
		int sizeX, sizeY;
	public:
		Tile **tiles;
		Field(const Field*);
		Field();
		~Field();	
		void SetSize(int, int);
		std::vector<int> GetSize();
};


#endif