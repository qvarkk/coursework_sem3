#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <bits/stdc++.h>

#include "game.h"

void Game::MenuInput(int *sel) {
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				if (*sel > 0)
					(*sel)--;
				break;
			case 's':
				if (*sel < 2)
					(*sel)++;
				break;
			case 13:
				switch (*sel) {
					case 0:
						StartGame();
						break;
					case 1:
						SetState(gsLeaderboard);
						break;
					case 2:
						SetState(gsSettings);
				}
				break;
			default:
				break;
		}
	}
}

void Game::SettingsInput(int *sel) {
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				if (*sel > 0)
					(*sel)--;
				break;
			case 's':
				if (*sel < 2)
					(*sel)++;
				break;
			case 'a':
				switch (*sel) {
					case 0:
						if (_GAME_SETTINGS[0] > 10)
							_GAME_SETTINGS[0] -= 10;
						break;
					case 1:
						if (_GAME_SETTINGS[1] > 5)
							_GAME_SETTINGS[1] -= 1;
						break;
					case 2:
						if (_GAME_SETTINGS[2] > 5)
							_GAME_SETTINGS[2] -= 1;
						break;
				}
				break;
			case 'd':
				switch (*sel) {
					case 0:
						if (_GAME_SETTINGS[0] < 500)
							_GAME_SETTINGS[0] += 10;
						break;
					case 1:
						if (_GAME_SETTINGS[1] < 20)
							_GAME_SETTINGS[1] += 1;
						break;
					case 2:
						if (_GAME_SETTINGS[2] < 20)
							_GAME_SETTINGS[2] += 1;
						break;
				}
				break;
			case 13:
				field->Setup(_GAME_SETTINGS[1], _GAME_SETTINGS[2]);
				SetState(gsMenu);
				break;
			default:
				break;
		}
	}
}

void Game::Process(int *sel, int *setSel) {
	switch (GetState()) {
		case gsMenu: 
		{
			PrintMenu(*sel);
			MenuInput(sel);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			system("cls"); 
			break;
		} 
		case gsLeaderboard:
			PrintLeaderboard();
			system("pause");
			system("cls"); 
			SetState(gsMenu);
			break;
		case gsSettings:
			PrintSettings(*setSel);
			SettingsInput(setSel);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			system("cls"); 
			break;
		case gsGame:
			Draw();
			Input();
			Logic();
			std::this_thread::sleep_for(std::chrono::milliseconds(_GAME_SETTINGS[0]));
			break;
	}
}

void Game::PrintMenu(int sel) {
	std::vector<std::string> menu = {"\t1. Play", "\t2. Leaderboards", "\t3. Settings"};
	std::cout << ">>-------> Menu <-------<< \n" << std::endl;
	for (int i = 0; i < 3; i++) {
		if (i == sel)
			std::cout << "->";
		std::cout << menu[i] << std::endl;
	}
	std::cout << "\n\nPress W or S to navigate menu" << std::endl;
}

void Game::PrintSettings(int setSel) {
	std::vector<std::string> settings = {"\tSpeed: ", "\tField Width: ", "\tField Height: ", "\tBack"};
	std::cout << ">>-------> Settings <-------<< \n" << std::endl;
	for (int i = 0; i < 3; i++) {
		if (i == setSel)
			std::cout << "->";
		std::cout << settings[i] << _GAME_SETTINGS[i] << std::endl;
	}
	std::cout << "\n\nPress W or S to navigate menu" << std::endl;
	std::cout << "Press A or D to change settings" << std::endl;
	std::cout << "Press Enter to return to menu" << std::endl;
}

void Game::StaleGame() {
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
			std::cout << "Your score: " << score << "\n\n" << std::endl;
			system("pause");
			WriteScore(score);
			ResetField();
			SetState(gsMenu);
			system("cls");
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
			std::cout << "\nSCORE: " << score  << "\n" << std::endl;
			system("pause");
			break;
	}
}

void Game::Draw() {
	system("cls");
	
	std::vector<int> size = field->GetSize();
	int sizeX = size[0], sizeY = size[1];
	
	std::vector<std::vector<eTile>> tiles = field->GetTiles();
	for (int i = 0; i < sizeY + 2; i++) {
		for (int j = 0; j < sizeX + 2; j++) {
			if (i == 0 || i == sizeY + 1 || j == 0 || j == sizeX + 1) {
				std::cout << "# ";
				continue;
			}
			
			switch(tiles[j - 1][i - 1]) {
				case HEAD:
					std::cout << "O ";
					break;
				case TAIL:
					std::cout << "o ";
					break;
				case FRUIT:
					std::cout << "X ";
					break;
				case EMPTY:
					std::cout << "  ";
					break;
				default:
					break;
			}
		}	
		std::cout << std::endl;
	}
	std::cout << "SCORE: " << score << std::endl;
	std::cout << "P - pause" << std::endl;
	std::cout << "Q - menu" << std::endl;
}

void Game::Input() {
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
				StaleGame();
				field->SetDirection(STOP);
				break;
			case 'q':
				ResetField();
				SetState(gsMenu);
				system("cls");
				break;
			default:
				break;
		}
	}
}

void Game::Logic() {
	eDir direction = field->GetDirection();
	if (direction == STOP)
		return;
	
	std::vector<std::vector<eTile>> tiles = field->GetTiles();
	std::vector<std::vector<int>> tail = field->GetTail();
	std::vector<int> size = field->GetSize();
	
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
	
	
	
	if (field->headX < 0 || field->headX >= size[0] ||
		field->headY < 0 || field->headY >= size[1]) {
			field->SetState(DEATH);
			StaleGame();
	}
	
	if (tiles[field->headX][field->headY] == TAIL) {
		field->SetState(DEATH);
		StaleGame();
	}
	
	field->SetTile(field->headX, field->headY, HEAD);
	
	if (tiles[field->headX][field->headY] == FRUIT) {
		score += (510 - _GAME_SETTINGS[0]) / 5;
		field->SpawnFruit();
		field->AddToTail(tail[tail.size() - 1][1], tail[tail.size() - 1][0]);
	}
}

void Game::StartGame() {
	ResetField();
	SetState(gsGame);
}

void Game::ResetField() {
	score = 0;
	std::vector<int> size = field->GetSize();
	field->Reset();
	field->Setup(size[0], size[1]);
}

void Game::WriteScore(int score) {
	std::fstream fs;
	fs.open("records.txt", std::fstream::in);
	
	std::string tmp;
	std::vector<int> records;
	
	while (getline(fs, tmp)) {
		tmp = tmp.substr(3);
  		records.push_back(std::stoi(tmp));
	}
	
	records.push_back(score);
	
	std::sort(records.begin(), records.end(), std::greater<int>());
		
	fs.close();

    fs.open("records.txt", std::fstream::out | std::fstream::trunc);
		
	for (int i = 0; i < records.size() && i < 9; i++) {
		fs << i + 1 << ". " << records[i] << "\n";
	}
	
	fs.flush();
	fs.close();
}

void Game::PrintLeaderboard() {
	std::fstream fs;
	fs.open("records.txt", std::fstream::in);
	
	std::string tmp;
	std::cout << " >>---------> Leaderboard <---------<< " << std::endl;
	while (getline(fs, tmp)) {
		std::cout << "\t\t" << tmp << std::endl;
	}
}