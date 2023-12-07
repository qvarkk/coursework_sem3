#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>

#include "field.h"

void StaleGame(Field* field, int* score) {
	switch (field->GetState()) {
		case DEATH:
		{
			system("cls");
			std::cout << "  ________                      ________                     " << std::endl;
			std::cout << " /  _____/_____    _____   ____ \\_____  \\___  __ ___________ " << std::endl;
			std::cout << "/   \\  ___\\__  \\  /     \\_/ __ \\ /   |   \\  \\/ // __ \\_  __ \\" << std::endl;
			std::cout << "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___//    |    \\   /\\  ___/|  | \\/" << std::endl;
			std::cout << " \\______  (____  /__|_|  /\\___  >_______  /\\_/  \\___  >__|   " << std::endl;
			std::cout << "        \\/     \\/      \\/     \\/        \\/          \\/       \n\n" << std::endl;
			std::cout << "Your score: " << *score << "\n\n" << std::endl;
			system("pause");
			*score = 0;
			std::vector<int> size = field->GetSize();
			field->Reset();
			field->Setup(size[0], size[1]);
			break;
		}
		case PAUSE:
			system("cls");
			std::cout << "__________                             " << std::endl;
			std::cout << "\\______   \\_____   __ __  ______ ____  " << std::endl;
			std::cout << " |     ___/\\__  \\ |  |  \\/  ___// __ \\ " << std::endl;
			std::cout << " |    |     / __ \\|  |  /\\___ \\\\  ___/ " << std::endl;
			std::cout << " |____|    (____  /____//____  >\\___  >" << std::endl;
			std::cout << "                \\/           \\/     \\/ \n\n" << std::endl;
			system("pause");
	}
}

void Draw(Field *field, int score) {
	system("cls");
	
	std::vector<int> size = field->GetSize();
	int sizeX = size[0], sizeY = size[1];
	
	std::vector<std::vector<eTile>> tiles = field->GetTiles();
	for (int i = 0; i < sizeY + 2; i++) {
		for (int j = 0; j < sizeX + 2; j++) {
			if (i == 0 || i == sizeX + 1 || j == 0 || j == sizeY + 1) {
				std::cout << "#";
				continue;
			}
			
			
			switch(tiles[j - 1][i - 1]) {
				case HEAD:
					std::cout << "O";
					break;
				case TAIL:
					std::cout << "o";
					break;
				case FRUIT:
					std::cout << "X";
					break;
				case EMPTY:
					std::cout << " ";
					break;
				default:
					break;
			}
		}	
		std::cout << std::endl;
	}
	std::cout << "SCORE: " << score << std::endl;
}

void Input(Field *field) {
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				if (field->GetDirection() != DOWN)
					field->SetDirection(UP);
				break;
			case 'a':
				if (field->GetDirection() != RIGHT)
					field->SetDirection(LEFT);
				break;
			case 's':
				if (field->GetDirection() != UP)
					field->SetDirection(DOWN);
				break;
			case 'd':
				if (field->GetDirection() != LEFT)
					field->SetDirection(RIGHT);
				break;
			case 'p':
				field->SetState(PAUSE);
				StaleGame(field, 0);
				field->SetDirection(STOP);
				break;
			default:
				break;
		}
	}
}

void Logic(Field *field, int *score) {
	eDir direction = field->GetDirection();
	if (direction == STOP)
		return;
	
	std::vector<std::vector<eTile>> tiles = field->GetTiles();
	std::vector<std::vector<int>> tail = field->GetTail();
	
	field->SetTile(field->headX, field->headY, EMPTY);
	
	int prevX, prevY, prev2X, prev2Y;
	
	prevX = tail[0][0];
	prevY = tail[0][1];
	tail[0][0] = field->headX;
	tail[0][1] = field->headY;
	
	for (int i = 1; i < tail.size(); i++) {
		prev2X = tail[i][0];
		prev2Y = tail[i][1];
		tail[i][0] = prevX;
		tail[i][1] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	field->SetTail(tail);
	field->UpdateField();
	
	switch (direction) {
		case UP:
			field->headY--;
			break;
		case DOWN:
			field->headY++;
			break;
		case LEFT:
			field->headX--;
			break;
		case RIGHT:
			field->headX++;
			break;
		default:
			break;
	}
	
	if (field->headX < 0 || field->headX > 19 ||
		field->headY < 0 || field->headY > 19) {
			field->SetState(DEATH);
			StaleGame(field, score);
	}
	
	if (tiles[field->headX][field->headY] == TAIL) {
		field->SetState(DEATH);
		StaleGame(field, score);
	}
	
	field->SetTile(field->headX, field->headY, HEAD);
	
	if (tiles[field->headX][field->headY] == FRUIT) {
		*score += 10;
		field->SpawnFruit();
		field->AddToTail(tail[tail.size() - 1][0], tail[tail.size() - 1][1]);
	}
}

int main(void) {
	int height = 20, width = 20;
	Field field(height, width);
	int score = 0;
	
	while (1) {
		Draw(&field, score);
		Input(&field);
		Logic(&field, &score);
		std::cout << field.GetDirection() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	
	return 0;
}
