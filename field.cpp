#include "field.h"

void Field::SetSize(int x, int y) {
	sizeX = x;
	sizeY = y;
}

std::vector<int> Field::GetSize() {
	std::vector<int> v;
	v.push_back(sizeX);
	v.push_back(sizeY);
	return v;
}