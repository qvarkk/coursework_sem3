#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "field.h"
#include "snake.h"

void Draw(Field);
void Logic(Snake);

int main(void) {
	Field field(20, 20);
	Field field2(20, 20);
	Field field3(20, 20);
	Snake snake;
	
	while (true) {
		Logic(snake);
		Draw(field3);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	
	return 0;
}

void Logic(Snake snake) {
	snake.MoveTail();
	
	snake.MoveHead();
}

void Draw(Field field) {
	system("cls");
	
	std::vector<int> size = field.GetSize();
	int sizeX = size[0], sizeY = size[1];
	
	for (int i = 0; i < sizeY + 2; i++) {
		for (int j = 0; j < sizeX + 2; j++) {
			if (i == 0 || i == sizeX + 1 || j == 0 || j == sizeY + 1) {
				std::cout << "#";
				continue;
			}
			
			Tile currTile = field.GetTile(j - 1, i - 1);
			std::vector<bool> tileState = currTile.GetState();
			if (tileState[0] == true) {
				std::cout << "o";
			} else if (tileState[1] == true) {
				std::cout << "X";
			} else {
				std::cout << " ";
			}
		}	
		std::cout << std::endl;
	}
}