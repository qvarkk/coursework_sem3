#ifndef GAME_H
#define GAME_H

#include "field.h"

enum GameState { gsMenu, gsLeaderboard, gsGame, gsSettings };

class Game {
	private:
		Field* field;
		int score;
		GameState state;
	public:
		Game(Field* field) { this->field = field; score = 0; }
		~Game() {}
		void MenuInput(int*);
		void SettingsInput(int*);
		void Process(int*, int*);
		void PrintMenu(int);
		void PrintSettings(int);
		std::vector<int> _GAME_SETTINGS = {150, 20, 20};
		void SetState(GameState state) { this->state = state; }
		GameState GetState() { return state; }
		void SetScore(int score) { this->score = score; }
		int GetScore() { return score; }
		void StaleGame();
		void Draw();
		void Input();
		void Logic();
		void StartGame();
		void ResetField();
		void WriteScore(int);
		void PrintLeaderboard();
};

#endif