#ifndef TILE_H
#define TILE_H

enum eTile { EMPTY = 0, BODY, HEAD, FRUIT };

class Tile {
	private:
		int posX, posY;
		eTile type;
	public:
		Tile(int, int);
		Tile(int, int, eTile);
		void SetPosition(int, int);
		void SetType(eTile);
		eTile GetType();
};

#endif