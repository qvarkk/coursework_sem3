#include <cstdlib>
#include "tile.h"

Tile::Tile(int posX, int posY) {
	SetType(EMPTY);
	SetPosition(posX, posY);
}

Tile::Tile(int posX, int posY, eTile type) {
	SetType(type);
	SetPosition(posX, posY);
}

void Tile::SetPosition(int posX, int posY) {
	this->posX = posX;
	this->posY = posY;
}

void Tile::SetType(eTile type) {
	this->type = type;
}

eTile Tile::GetType() {
	return type;
}

