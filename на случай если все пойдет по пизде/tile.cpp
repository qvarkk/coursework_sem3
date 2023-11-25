#include "tile.h"

Tile::Tile() {
	SetPos(0, 0);
	SetState(0, 0);
}

Tile::Tile(int posX, int posY, bool snake, bool fruit) {
	SetPos(posX, posY);
	SetState(snake, fruit);
}

void Tile::SetPos(int x, int y) {
	posX = x;
	posY = y;
}

void Tile::SetState(bool snake, bool food) {
	hasSnake = snake;
	hasFood = food;
}

std::vector<int> Tile::GetPos() {
	std::vector<int> v;
	v.push_back(posX);
	v.push_back(posY);
	return v;
}

std::vector<bool> Tile::GetState() {
	std::vector<bool> v;
	v.push_back(hasSnake);
	v.push_back(hasFood);
	return v;
}