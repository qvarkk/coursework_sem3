#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "tile.h"

enum eDirection {
			STOP = 0,
			UP,
			DOWN,
			LEFT,
			RIGHT
};

class Snake {
	private:
		Tile head;
		std::vector<Tile> tail;
		int tailLen;
		int lastX, lastY, last2X, last2Y;
		eDirection dir;
	public:
		Snake();
		Tile GetHead();
		std::vector<Tile> GetTail();
		int GetTailLen();
		eDirection GetDirection();
		std::vector<int> GetLasts();
		void SetHead(int, int);
		void AddTail();
		void MoveTail();
		void SetTailLen(int);
		void SetDirection(eDirection);
		void SetLasts(int, int, int, int);
		void MoveHead();
};

#endif