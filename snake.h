#ifndef SNAKE_H
#define SNAKE_H

# include "tile.h"

class Snake {
	public:
		Snake(const Snake*);
		Snake();
		~Snake();
		Tile head, tail;
		Tile *body;
};

#endif