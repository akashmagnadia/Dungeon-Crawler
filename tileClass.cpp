#include "amagna2Proj7.h"

tileClass::tileClass() {
	element = ' ';
	score = 0;
	file = "";
}

void tileClass::setElementEmpty() {
	element = ' ';
}

void tileClass::setElementWall() {
	element = '*';
}

void tileClass::setElementChest(int _score) {
	element = 'C';
	score += _score;
}

void tileClass::setElementDoor() {
	element = 'D';
}

void tileClass::setElementExit() {
	element = 'E';
}

char tileClass::getElement() {
	return element;
}

int tileClass::getScore() {
	return score;
}

void tileClass::setElementPlayer() {
	element = 'P';
}

void tileClass::setFileName(string incomingFile) {
	file = incomingFile;
}

string tileClass::getFileName() {
	return file;
}

chestClass::chestClass() {
	element = 'C';
	score = 0;
}

void chestClass::setElementChest(int _score) {
	element = 'C';
	score += _score;
}

int chestClass::getScore() {
	return score;
}

doorClass::doorClass() {
	element = 'D';
}

void doorClass::setElementDoor(string door) {
	return;
}

wallClass::wallClass() {
	element = '*';
}

void wallClass::setElementWall() {
	return;
}
