#include <iostream>
#include "snake.h"

Snake::Snake() {
	Tile head(10, 10, true, false);
	tail.push_back(head);
	tailLen = 0;
	lastX = 0;
	lastY = 0;
	last2X = 0;
	last2Y = 0;
	dir = UP;
}

Tile Snake::GetHead() {
	return head;
}

std::vector<Tile> Snake::GetTail() {
	return tail;
}

int Snake::GetTailLen() {
	return tailLen;
}

eDirection Snake::GetDirection() {
	return dir;
}

std::vector<int> Snake::GetLasts() {
	std::vector<int> v;
	v.push_back(lastX);
	v.push_back(lastY);
	v.push_back(last2X);
	v.push_back(last2Y);
	return v;
}

void Snake::SetHead(int posX, int posY) {
	this->head.SetPos(posX, posY);
}

void Snake::AddTail() {
	tailLen++;
	std::vector<int> v = tail.back().GetPos();
	Tile tile(v[0], v[1], true, false);
	tail.push_back(tile);
}

void Snake::MoveTail() {
	std::vector<int> zeroPos = tail[0].GetPos();
	lastX = zeroPos[0];
	lastY = zeroPos[1];
	std::vector<int> headPos = head.GetPos();
	tail[0].SetPos(headPos[0], headPos[1]);
	
	for (int i = 1; i < tailLen; i++) {
		std::vector<int> currPos = tail[i].GetPos();
		last2X = currPos[0];		
		last2Y = currPos[1];
		tail[i].SetPos(lastX, lastY);
		lastX = last2X;
		lastY = last2Y;
	}
}

void Snake::SetTailLen(int tailLen) {
	this->tailLen = tailLen;
}

void Snake::SetDirection(eDirection dir) {
	this->dir = dir;
}

void Snake::SetLasts(int lastX, int lastY, int last2X, int last2Y) {
	this->lastX = lastX;
	this->lastY = lastY;
	this->last2X = last2X;
	this->last2Y = last2Y;
}

void Snake::MoveHead() {
	std::vector<int> headPos = head.GetPos();
	
	switch (dir) {
		case UP:
			head.SetPos(headPos[0] + 1, headPos[1]);
			break;
		case DOWN:
			head.SetPos(headPos[0] - 1, headPos[1]);
			break;
		case LEFT:
			head.SetPos(headPos[0], headPos[1] - 1);
			break;
		case RIGHT:
			head.SetPos(headPos[0], headPos[1] + 1);
			break;
		default:
			break;
	}
}