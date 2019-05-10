#ifndef amagna2Proj7_h
#define amagna2Proj7_h

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <fstream>
using namespace std;


class tileClass {
private:
	char element;
	int score;
	string file;

public:
	tileClass();
	//~tileClass();

	void setElementEmpty();
	void setElementWall();
	void setElementChest(int _score);
	void setElementDoor();
	void setElementExit();
	char getElement();
	int getScore();
	void setElementPlayer();
	void setFileName(string incomingFile);
	string getFileName();
};


class chestClass : public tileClass {
private:
	char element;
	int score;

public:
	chestClass();
	//~chestClass();

	void setElementChest(int _score);
	int getScore();
};


class doorClass : public tileClass {
private:
	char element;

public:
	doorClass();
	//~doorClass();

	void setElementDoor(string door);
};


class wallClass : public tileClass {
private:
	char element;

public:
	wallClass();
	//~wallClass();

	void setElementWall();
};


class playerClass {
private:
	int x_Size;
	int y_Size;
	int currentPosition;
	int score;
	int tilesVisited;

public:
	playerClass();
	//~playerClass();

	void setXSize(int xSize);
	void setYSize(int ySize);
	int getScore();
	void increaseScore(int scoreToAdd);
	void setXYtoPos(int x, int y);
	int getXYtoPos(int x, int y);
	int getXPosition();
	int getXPosition(int position);
	int getYPosition();
	int getYPosition(int position);
	void incrementVTilesVisited();
	int getTilesVisited();
};

class roomClass {
private:
	tileClass* matrix;
	playerClass player;
	int x_Size;
	int y_Size;
	int visited;

public:
	roomClass();

	// The main loop for reading in input
	void processCommandLoop(string inFile);
	void showCommands();
	void setPlayer(int x, int y);
	void setWall(int x, int y);
	void setChest(int x, int y, int chestScore);
	void setExit(int x, int y);
	void setDoor(int x, int y, string fileName);
	bool goUp(bool& newRoom);
	bool goDown(bool& newRoom);
	bool goLeft(bool& newRoom);
	bool goRight(bool& newRoom);
	void dfs();
	//void _dfs(bool* visitedMatrix[], int xPlayerPos, int yPlayerPos, bool* doorFound);

	//destructor
	void remove();

	//helper functions
	int getXSize();
	int getYSize();
	void setXSize(int xSize);
	void setYSize(int ySize);
	int stringToInt(string input);
	bool skipEmptySpace(string input, int& i);
	bool getXYfromInput(string input, int startingI, int& i, bool checkXY, int& x, int& y);
	void setupRoom(int x, int y);
	void startLocation(int xStart, int yStart);
	bool isExit(int x, int y);
	bool isWall(int x, int y);
	bool isChest(int x, int y);
	bool isDoor(int x, int y);
	void freeUpRoom();

	//testing purposes
	void printBoard();
};

#endif
