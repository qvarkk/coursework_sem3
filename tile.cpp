#include "tile.h"

Tile::Tile(const Tile* tile) {
	std::vector<int> pos = tile->GetPos();
	SetPos(pos[0], pos[1]);
	std::vector<bool> state = tile->GetState();
	SetState(state[0], state[1]);
}

Tile::Tile() {
	SetPos(0, 0);
	SetState(0, 0);
}

Tile::~Tile() {
	Clear();
}

void Tile::SetPos(int x, int y) {
	posX = x;
	posY = y;
}

void Tile::SetState(bool snake, bool food) {
	hasSnake = snake;
	hasFood = food;
}

std::vector<int> GetPos() {
	std::vector<int> v;
	v.push_back(posX);
	v.push_back(posY);
	return v;
}

std::vector<bool> GetState() {
	std::vector<bool> v;
	v.push_back(hasSnake);
	v.push_back(hasFood);
	return v;
}
 
void Tile::Clear() {
	SetPos(0, 0);
	SetState(0, 0);
}