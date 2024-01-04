#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>

#include "field.h"
#include "game.h"

int main(void) {
	Field field(20, 20);
	Game game(&field);

	int sel = 0, setSel = 0;

	while (1) {	
		game.Process(&sel, &setSel);
	}
	
	return 0;
}