#include <cstdlib>
#include <iostream>
#include "field.h"

Field::Field(int sizeX, int sizeY) {
	SetSize(sizeX, sizeY);
	
	tiles = new Tile*[sizeY];
	for(int i = 0; i < sizeY; i++)
    	tiles[i] = new Tile[sizeX];
    	
    for (int i = 0; i < sizeX; i++) {
    	for (int j = 0; j < sizeY; j++) {
    		tiles[i][j].SetPos(i, j);
		}
	}
}

Field::~Field() {
	for (int i = 0; i < sizeY; ++i) {
		delete [] tiles[i];
	}
	delete [] tiles;
}

void Field::SetSize(int sizeX, int sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

std::vector<int> Field::GetSize() {
	std::vector<int> v;
	v.push_back(sizeX);
	v.push_back(sizeY);
	return v;
}

Tile Field::GetTile(int posX, int posY) {
	return tiles[posX][posY];
}