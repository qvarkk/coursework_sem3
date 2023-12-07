#include <cstdlib>
#include "field.h"

Field::Field(int height, int width) {
	Setup(height, width);
}

void Field::Reset() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tiles[i][j] = EMPTY;
		}
	}
	
	tail.resize(0);
}

void Field::Setup(int height, int width) {
	SetSize(height, width);
	SetDirection(STOP);
	tiles.resize(height);		
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
	}
	
	tiles[width/2][height/2] = HEAD;
	headX = width/2;
	headY = height/2;
	
	AddToTail(width/2 - 1, height/2);
	AddToTail(width/2 - 2, height/2);
	AddToTail(width/2 - 3, height/2);
	
	UpdateField();
	
	SpawnFruit();
}

void Field::SetSize(int height, int width) {
	this->height = height;
	this->width = width;
}

std::vector<int> Field::GetSize() {
	std::vector<int> v;
	v.push_back(height);
	v.push_back(width);
	return v;
}

void Field::SetTile(int posX, int posY, eTile type) {
	tiles[posX][posY] = type;
}

std::vector<std::vector<eTile>> Field::GetTiles() {
	return tiles;
}

void Field::SetDirection(eDir direction) {
	this->direction = direction;
}

eDir Field::GetDirection() {
	return direction;
}

void Field::SpawnFruit() {
	tiles[rand() % width][rand() % height] = FRUIT;
}

void Field::AddToTail(int posX, int posY) {
	tiles[posX][posY] = TAIL;
	std::vector<int> v;
	v.push_back(posX);
	v.push_back(posY);
	tail.push_back(v);
}

std::vector<std::vector<int>> Field::GetTail() {
	return tail;
}

void Field::SetTail(std::vector<std::vector<int>> tail) {
	this->tail = tail;
}

void Field::UpdateField() {	
	for (int i = 0; i < tail.size(); i++) {
		tiles[tail[i][0]][tail[i][1]] = TAIL;
	}
	
	tiles[tail[tail.size() - 1][0]][tail[tail.size() - 1][1]] = EMPTY;
}

void Field::SetState(eState state) {
	this->state = state;
}

eState Field::GetState() {
	return state;
}
