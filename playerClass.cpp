#include "amagna2Proj7.h"

playerClass::playerClass() {
	x_Size = 0;
	y_Size = 0;
	currentPosition = 0;
	score = 0;
	tilesVisited = 0;
}

void playerClass::setXSize(int xSize) {
	x_Size = xSize;
}

void playerClass::setYSize(int ySize) {
	y_Size = ySize;
}

int playerClass::getScore() {
	return score;
}

void playerClass::increaseScore(int scoreToAdd) {
	score = score + scoreToAdd;
}

void playerClass::setXYtoPos(int x, int y) {
	//xSize = width
	currentPosition = ((x_Size * y) + x);
}

int playerClass::getXYtoPos(int x, int y) {
	//xSize = width
	return ((x_Size * y) + x);
}

int playerClass::getXPosition() {
	//xSize = width
	return currentPosition % x_Size;
}

int playerClass::getYPosition() {
	//xSize = width
	return currentPosition / x_Size;
}

void playerClass::incrementVTilesVisited() {
	tilesVisited = tilesVisited + 1;
}

int playerClass::getTilesVisited() {
	return tilesVisited;
}

int playerClass::getXPosition(int position) {
	//xSize = width
	return position % x_Size;
}

int playerClass::getYPosition(int position) {
	//xSize = width
	return position % x_Size;
}
