#ifndef TILE_H
#define TILE_H

#include <vector>

class Tile {
	private:	
		bool hasSnake, hasFood;
		int posX, posY;
	public:
		Tile();
		Tile(int, int, bool, bool);
		void SetPos(int, int);
		void SetState(bool, bool);
		std::vector<int> GetPos();
		std::vector<bool> GetState();
		void Clear();
};

#endif