#ifndef FIELD_H
#define FIELD_H

#include <vector>

enum eTile { EMPTY = 0, TAIL, HEAD, FRUIT };
enum eDir { STOP = 0, UP, DOWN, LEFT, RIGHT };
enum eState { PLAY = 0, PAUSE, DEATH };

class Field {
	private:
		int height, width;
		std::vector<std::vector<eTile>> tiles;
		std::vector<std::vector<int>> tail;
		eDir direction;
		eState state;
	public:
		int headX, headY;
		Field(int, int);
		void Reset();
		void Setup(int, int);
		void SetSize(int, int);
		std::vector<int> GetSize();
		void SetTile(int, int, eTile);
		std::vector<std::vector<eTile>> GetTiles();
		void SetDirection(eDir);
		eDir GetDirection();
		void SpawnFruit();
		void AddToTail(int, int);
		void SetTail(std::vector<std::vector<int>>);
		std::vector<std::vector<int>> GetTail();
		void UpdateField();
		void SetState(eState);
		eState GetState();
};

#endif