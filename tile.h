#ifndef TILE_H
#define TILE_H

#include <vector>

class Tile {
	public:
		bool hasSnake, hasFood;
		int posX, posY;
		Tile(const Tile*);
		Tile();
		~Tile();
		void SetPos(int, int);
		void SetState(bool, bool);
		std::vector<int> GetPos();
		std::vector<bool> GetState();
		void Clear();
};

#endif