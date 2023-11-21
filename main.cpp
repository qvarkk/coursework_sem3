#include <iostream>
#include <cstdlib>
#include <vector>

#include "field.h"

void Draw(Field);

int main(void) {
	Field field;
	field.SetSize(20, 20);
	Draw(field);
}

void Draw(Field field) {
	system("cls");
	
	std::vector<int> size = field.GetSize();
	int sizeX = size[0];
	int sizeY = size[1];
	
	for (int i = 0; i < sizeX + 2; i++) {
		for (int j = 0; j < sizeY + 2; j++) {
			if (i == 0 || i == sizeX + 1 || j == 0 || j == sizeY + 1) {
				std::cout << "#";
				continue;
			}
			
			std::vector<bool> tileState = field.tiles[i - 1][j - 1].GetState();
			if (tileState[0] == true) {
				std::cout << "o";
			} else if (tileState[1] == true) {
				std::cout << "X";
			} else {
				std::cout << " ";
			}
			system("pause");
		}	
		std::cout << std::endl;
	}
}