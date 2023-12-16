#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>

#include "field.h"
#include "game.h"

int _SPEED = 100;
int _SIZE_X = 20;
int _SIZE_Y = 20;

void MenuInput(Game *game, int *sel) {
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				*sel = 0;
				break;
			case 's':
				*sel = 1;
				break;
			case 13:
				switch (*sel) {
					case 0:
						game->StartGame();
						break;
					case 1:
						game->SetState(gsLeaderboard);
						break;
				}
				break;
			default:
				break;
		}
	}
}

int main(void) {
	int height = _SIZE_X, width = _SIZE_Y;
	Field field(height, width);
	Game game(&field);
	
	std::vector<std::string> menu = {"\t1. Play", "\t2. Leaderboards"};
	int sel = 0;
	
	while (1) {	
		switch (game.GetState()) {
			case gsMenu: 
			{
				std::cout << ">>-------> Menu <-------<< \n" << std::endl;
				for (int i = 0; i < 2; i++) {
					if (i == sel)
						std::cout << "->";
					std::cout << menu[i] << std::endl;
				}
				std::cout << "\n\nPress W or S to navigate menu" << std::endl;
				MenuInput(&game, &sel);
				std::this_thread::sleep_for(std::chrono::milliseconds(250));
				system("cls"); 
				break;
			} 
			case gsLeaderboard:
				game.PrintLeaderboard();
				system("pause");
				system("cls"); 
				game.SetState(gsMenu);
				break;
			case gsGame:
				game.Draw();
				game.Input();
				game.Logic();
				std::this_thread::sleep_for(std::chrono::milliseconds(_SPEED));
				break;
		}
	}
	
	return 0;
}
