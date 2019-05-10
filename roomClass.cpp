#include "amagna2Proj7.h"

roomClass::roomClass() { //constructor
	matrix = NULL;
	player = *new playerClass;
	x_Size = 0;
	y_Size = 0;
	visited = 0;
}

// The main loop for reading in input
void roomClass::processCommandLoop(string inFile)
{
	bool startPositionSet = false;
	bool sizeSet = false;
	bool newRoom = true;

	ifstream file;

	string input = ""; //initialization of string input
	string fileName = inFile;

	//file is read to argv

	// loop until all lines are read from the input
	//getline(file, input) to get input from file
	//getline(cin, input) to get input from terminal

	while (newRoom) {
		newRoom = false;
		startPositionSet = false;
		sizeSet = false;

		cout << "Opening " << fileName;

		file.open(fileName);
		input = "";

		if (!file.is_open()) {
			cout << "File couldn't be opened" << endl;
			freeUpRoom();
			exit(1);
		}

		cout << endl;
		cout << "Making a new dungeon... Hold tight" << endl << endl;
		cout << "I asked multiple times on Piaaza if position starts with 0 or 1, but I didn't get any response from any instructor" << endl;
		cout << "Therefore, I have made my own coordinate system which starts from 0 and works as intended" << endl << endl;
		while (getline(file, input))
		{
			//cout << input.at(0) << " " << input.length() << endl;
			if (!sizeSet) { //set the size of matrix
				int startingI = 0, i = 0;
				bool checkXY = false;
				if (getXYfromInput(input, startingI, i, checkXY, x_Size, y_Size)) {
					setupRoom(x_Size, y_Size);
					sizeSet = true;
				}
				else {
					cout << "Operation Failed: Size of the board not set" << endl;
				}
				continue;
			}

			if ((input.at(0) == 'q') || (input.at(0) == 'Q')) {
				file.close();
				freeUpRoom();
				return;
			}
			else if (((input.at(0) == 's') || (input.at(0) == 'S')) && (!startPositionSet)) {
				int i = 0, x = 0, y = 0;
				int startingI = 1;
				bool checkXY = true;
				if (getXYfromInput(input, startingI, i, checkXY, x, y)) {
					startPositionSet = true;
					setPlayer(x, y);
				}
				else {
					cout << "Operation Failed: Player starting position not set" << endl;
				}
			}
			else if ((input.at(0) == 'o') || (input.at(0) == 'O')) {
				int i = 0, x = 0, y = 0;
				int startingI = 1;
				bool checkXY = true;
				if (getXYfromInput(input, startingI, i, checkXY, x, y)) {
					setWall(x, y);
				}
				else {
					cout << "Operation Failed: Wall not set" << endl;
				}
			}
			else if ((input.at(0) == 'c') || (input.at(0) == 'C')) {
				int i = 0, x = 0, y = 0, score = 0;
				int startingI = 1;
				bool checkXY = true;
				if (getXYfromInput(input, startingI, i, checkXY, x, y)) {
					string current = "";
					int length = input.length();

					if (!skipEmptySpace(input, i)) {
						cout << "Operation Failed: Chest score not found" << endl;
						break;
					}

					while (input.at(i) != ' ') { //pick out individual words
						current.push_back(input.at(i));
						i++; //move to next character or number

						if (i >= length) {
							break; //end of input
						}
					}

					score = stringToInt(current);
					setChest(x, y, score);
				}
				else {
					cout << "Operation Failed: Chest not set" << endl;
				}
			}
			else if (((input.at(0) == 'd') || (input.at(0) == 'D')) && (input.length() > 2)) {
				int i = 0, x = 0, y = 0, score = 0;
				int startingI = 1;
				bool checkXY = true;
				if (getXYfromInput(input, startingI, i, checkXY, x, y)) {
					string current = "";
					int length = input.length();

					if (!skipEmptySpace(input, i)) {
						cout << "Operation Failed: Filename not found" << endl;
						break;
					}

					while (input.at(i) != ' ') { //pick out individual words
						current.push_back(input.at(i));
						i++; //move to next character or number

						if (i >= length) {
							break; //end of input
						}
					}

					setDoor(x, y, current);
				}
				else {
					cout << "Operation Failed: Door not set" << endl;
				}
			}
			else if ((input.at(0) == 'e') || (input.at(0) == 'E')) {
				int i = 0, x = 0, y = 0;
				int startingI = 1;
				bool checkXY = true;
				if (getXYfromInput(input, startingI, i, checkXY, x, y)) {
					setExit(x, y);
				}
				else {
					cout << "Operation Failed: Exit not set" << endl;
				}
			}
			else if ((input.at(0) == 'h') || (input.at(0) == 'H')) {
				showCommands();
			}
			else if ((input.at(0) == 'g') || (input.at(0) == 'G')) {
				cout << "Score: " << player.getScore() << endl;
			}
			else if ((input.at(0) == 'w') || (input.at(0) == 'W')) {
				//cout << "At W" << endl;
				if (startPositionSet) {
					goUp(newRoom);
					if (newRoom) {
						int xPos = player.getXPosition();
						int yPos = player.getYPosition();
						fileName = matrix[player.getXYtoPos(xPos, yPos - 1)].getFileName();
						file.close();
						break;
					}
				}
				else {
					cout << "Operation Failed: Player's position is not set" << endl;
				}

			}
			else if ((input.at(0) == 's') || (input.at(0) == 'S')) {
				//
				if (startPositionSet) {
					goDown(newRoom);
					if (newRoom) {
						int xPos = player.getXPosition();
						int yPos = player.getYPosition();
						fileName = matrix[player.getXYtoPos(xPos, yPos + 1)].getFileName();
						file.close();
						break;
					}
				}
				else {
					cout << "Operation Failed: Player's position is not set" << endl;
				}

			}
			else if ((input.at(0) == 'a') || (input.at(0) == 'A')) {
				//
				if (startPositionSet) {
					goLeft(newRoom);
					if (newRoom) {
						int xPos = player.getXPosition();
						int yPos = player.getYPosition();
						fileName = matrix[player.getXYtoPos(xPos - 1, yPos)].getFileName();
						file.close();
						break;
					}
				}
				else {
					cout << "Operation Failed: Player's position is not set" << endl;
				}

			}
			else if ((input.at(0) == 'd') || (input.at(0) == 'D')) {
				//
				if (startPositionSet) {
					goRight(newRoom);
					if (newRoom) {
						int xPos = player.getXPosition();
						int yPos = player.getYPosition();
						fileName = matrix[player.getXYtoPos(xPos + 1, yPos)].getFileName();
						file.close();
						break;
					}
				}
				else {
					cout << "Operation Failed: Player's position is not set" << endl;
				}

			}
			else if ((input.at(0) == 'f') || (input.at(0) == 'F')) {
				dfs();
			}
			else if ((input.at(0) == 'b') || (input.at(0) == 'B')) {
				dfs();
			}
			else if ((input.at(0) == 'p') || (input.at(0) == 'P')) {
				printBoard();
			}
			else {
				cout << "Command not recognized" << endl;
			}
		}
	}

}

void roomClass::showCommands()
{
	printf("The commands for this project are:\n");
	printf("  Q to exit the program \n");
	printf("  H to display commands \n");
	printf("  W to go up \n");
	printf("  S to go down \n");
	printf("  A to go left \n");
	printf("  D to go right \n");
	printf("  G to print the score \n");
	printf("  F to find a path \n");
	printf("  P to print the maze \n \n");

	printf("  For Setup of Room: \n");
	printf("  X Y (size X by Y) \n");
	printf("  S X Y (Start location of person) \n");
	printf("  O X Y (List of obstacles) \n");
	printf("  C X Y Point_Value (chests) \n");
	printf("  D X Y <filename.txt> \n");
	printf("  E X Y (Dungeon Exit, will only be in 1 file) \n");
}

void roomClass::setPlayer(int x, int y) {
	player.setXYtoPos(x, y); //set the position of player
	matrix[player.getXYtoPos(x, y)].setElementPlayer();
}

void roomClass::setWall(int x, int y) {
	matrix[player.getXYtoPos(x, y)].setElementWall();
}

void roomClass::setChest(int x, int y, int chestScore) {
	matrix[player.getXYtoPos(x, y)].setElementChest(chestScore);
}

void roomClass::setExit(int x, int y) {
	matrix[player.getXYtoPos(x, y)].setElementExit();
}

void roomClass::setDoor(int x, int y, string fileName) {
	matrix[player.getXYtoPos(x, y)].setElementDoor();
	matrix[player.getXYtoPos(x, y)].setFileName(fileName);
}

bool roomClass::goUp(bool& newRoom) {
	int xPos = player.getXPosition();
	int yPos = player.getYPosition();

	if (((xPos) >= x_Size) || ((yPos - 1) >= y_Size) || ((xPos) < 0) || ((yPos - 1) < 0)) {
		cout << "X Y coordinate is out of range" << endl;
		return false;
	}

	if (isWall(xPos, yPos - 1)) {
		cout << "Obstacle Detected" << endl;
		return false;
	}

	player.incrementVTilesVisited();

	if (isExit(xPos, yPos - 1)) {
		cout << "Exit Detected" << endl;
		cout << "Escaping the Dungeon" << endl;
		cout << "After taking " << player.getTilesVisited() << " steps, the player escaped with " << player.getScore() << " gold and happily lived ever after" << endl;
		freeUpRoom();
		exit(1);
	}

	if (isChest(xPos, yPos - 1)) {
		cout << "Chest Detected with " << matrix[player.getXYtoPos(xPos, yPos - 1)].getScore() << " gold" << endl;
		player.increaseScore(matrix[player.getXYtoPos(xPos, yPos - 1)].getScore());
	}

	if (isDoor(xPos, yPos - 1)) {
		cout << "Door Detected" << endl;
		newRoom = true;
		return true;
	}

	//if everything goes well then
	matrix[player.getXYtoPos(xPos, yPos)].setElementEmpty();
	matrix[player.getXYtoPos(xPos, yPos - 1)].setElementPlayer();
	player.setXYtoPos(xPos, yPos - 1);
	return true;
}

bool roomClass::goDown(bool& newRoom) {
	int xPos = player.getXPosition();
	int yPos = player.getYPosition();

	if (((xPos) >= x_Size) || ((yPos + 1) >= y_Size) || ((xPos) < 0) || ((yPos + 1) < 0)) {
		cout << "X Y coordinate is out of range" << endl;
		return false;
	}

	if (isWall(xPos, yPos + 1)) {
		cout << "Wall Detected" << endl;
		return false;
	}

	player.incrementVTilesVisited();

	if (isExit(xPos, yPos + 1)) {
		cout << "Exit Detected" << endl;
		cout << "Escaping the Dungeon" << endl;
		cout << "After taking " << player.getTilesVisited() << " steps, the player escaped with " << player.getScore() << " gold and happily lived ever after" << endl;
		exit(1);
	}

	if (isChest(xPos, yPos + 1)) {
		cout << "Chest Detected with " << matrix[player.getXYtoPos(xPos, yPos + 1)].getScore() << " gold" << endl;
		player.increaseScore(matrix[player.getXYtoPos(xPos, yPos + 1)].getScore());
	}

	if (isDoor(xPos, yPos + 1)) {
		cout << "Door Detected" << endl;
		newRoom = true;
		return true;
	}

	//if everything goes well then
	matrix[player.getXYtoPos(xPos, yPos)].setElementEmpty();
	matrix[player.getXYtoPos(xPos, yPos + 1)].setElementPlayer();
	player.setXYtoPos(xPos, yPos + 1);
	return true;
}

bool roomClass::goLeft(bool& newRoom) {
	int xPos = player.getXPosition();
	int yPos = player.getYPosition();

	if (((xPos - 1) >= x_Size) || ((yPos) >= y_Size) || ((xPos - 1) < 0) || ((yPos) < 0)) {
		cout << "X Y coordinate is out of range" << endl;
		return false;
	}

	if (isWall(xPos - 1, yPos)) {
		cout << "Wall Detected" << endl;
		return false;
	}

	player.incrementVTilesVisited();

	if (isExit(xPos - 1, yPos)) {
		cout << "Exit Detected" << endl;
		cout << "Escaping the Dungeon" << endl;
		cout << "After taking " << player.getTilesVisited() << " steps, the player escaped with " << player.getScore() << " gold and happily lived ever after" << endl;
		exit(1);
	}

	if (isChest(xPos - 1, yPos)) {
		cout << "Chest Detected with " << matrix[player.getXYtoPos(xPos - 1, yPos)].getScore() << " gold" << endl;
		player.increaseScore(matrix[player.getXYtoPos(xPos - 1, yPos)].getScore());
	}

	if (isDoor(xPos, yPos - 1)) {
		cout << "Door Detected" << endl;
		newRoom = true;
		return true;
	}

	//if everything goes well then
	matrix[player.getXYtoPos(xPos, yPos)].setElementEmpty();
	matrix[player.getXYtoPos(xPos - 1, yPos)].setElementPlayer();
	player.setXYtoPos(xPos - 1, yPos);
	return true;
}

bool roomClass::goRight(bool& newRoom) {
	int xPos = player.getXPosition();
	int yPos = player.getYPosition();

	if (((xPos + 1) >= x_Size) || ((yPos) >= y_Size) || ((xPos + 1) < 0) || ((yPos) < 0)) {
		cout << "X Y coordinate is out of range" << endl;
		return false;
	}

	if (isWall(xPos + 1, yPos)) {
		cout << "Wall Detected" << endl;
		return false;
	}

	player.incrementVTilesVisited();

	if (isExit(xPos + 1, yPos)) {
		cout << "Exit Detected" << endl;
		cout << "Escaping the Dungeon" << endl;
		cout << "After taking " << player.getTilesVisited() << " steps, the player escaped with " << player.getScore() << " gold and happily lived ever after" << endl;
		exit(1);
	}

	if (isChest(xPos + 1, yPos)) {
		cout << "Chest Detected with " << matrix[player.getXYtoPos(xPos + 1, yPos)].getScore() << " gold" << endl;
		player.increaseScore(matrix[player.getXYtoPos(xPos + 1, yPos)].getScore());
	}

	if (isDoor(xPos, yPos - 1)) {
		cout << "Door Detected" << endl;
		newRoom = true;
		return true;
	}

	//if everything goes well then
	matrix[player.getXYtoPos(xPos, yPos)].setElementEmpty();
	matrix[player.getXYtoPos(xPos + 1, yPos)].setElementPlayer();
	player.setXYtoPos(xPos + 1, yPos);
	return true;
}

void roomClass::dfs() {
	for (int i = 0; i < x_Size * y_Size; i++) {
		if (matrix[i].getElement() == 'D') {
			cout << "Path to door found at (" << player.getXPosition(i) << ", " << player.getYPosition(i) << ")" << endl;
			return;
		}
	}
	cout << "Path to door not found" << endl;
}
//void roomClass::dfs() {
//	bool *visitedMatrix = new bool[x_Size * y_Size]; 
//	bool doorFound;
//
//	//set all of them as unvisited and the walls adn exit as visited
//	for (int i = 0; i < (x_Size * y_Size); i++) {
//		if (matrix[i].getElement() == ('*' || 'E')) {
//			if (visitedMatrix[i] == true) {
//				cout << "Error Encountered" << endl;
//			}
//			visitedMatrix[i] = true; //visited
//		}
//		else {
//			visitedMatrix[i] = false; //unvisited
//		}
//	}
//
//	int xPlayerPos = player.getXPosition();
//	int yPlayerPos = player.getYPosition();
//	_dfs(visitedMatrix, xPlayerPos, yPlayerPos, doorFound);
//
//	//free up tempMatrix
//}

//void roomClass::_dfs(bool visitedMatrix[], int xPlayerPos, int yPlayerPos, bool *doorFound) {
//	int* fourDir = new int[4];
//	bool temp = true;
//
//	for (int i = 0; i < 4; i++) {
//		//go left
//		if ((xPlayerPos - 1 < x_Size - 1) || (visitedMatrix[player.getXYtoPos(xPlayerPos - 1, yPlayerPos)] == true)) {
//
//		}
//	}
//	
//
//	//go left first
//	
//}


//helper functions

int roomClass::getXSize() {
	return x_Size;
}

int roomClass::getYSize() {
	return y_Size;
}

void roomClass::setXSize(int xSize) {
	x_Size = xSize;
	player.setXSize(xSize);
}

void roomClass::setYSize(int ySize) {
	y_Size = ySize;
	player.setYSize(ySize);
}

int roomClass::stringToInt(string input) {
	int tempNum = atoi(input.c_str());

	if (errno == EDOM) {
		cout << "Expected an integer." << endl;
		cout << "In case you forgot your numbers:" << endl;
		cout << "1 2 3 4 5 6 7 8 9 0" << endl;
		exit(1); //if something is wrong with tempNum
	}

	return tempNum;
}

bool roomClass::skipEmptySpace(string input, int& i) {
	int length = input.length();
	if (i >= length) {
		cout << "Operation Failed" << endl;
		return false;
	}
	while (input.at(i) == ' ') { //get to something that has value
		if (i >= length) {
			cout << "Operation Failed" << endl;
			return false;
		}
		i++;
	}
	return true; //if successful
}

bool roomClass::getXYfromInput(string input, int startingI, int& i, bool checkXY, int& x, int& y) {
	string current = "";
	int length = input.length();
	x = 1;
	y = 1;
	i = startingI;

	if (i >= length) {
		cout << "Operation Failed" << endl;
		return false;
	}

	//return true if successful
	if (!skipEmptySpace(input, i)) {
		return false;
	}

	while (input.at(i) != ' ') { //pick out individual words
		current.push_back(input.at(i));
		i++; //move to next character or number

		if (i >= length) {
			cout << "Value of the y position not entered" << endl;
			return false;
		}
	}

	x = stringToInt(current); //store the x position of player
	current = ""; //reset the string for use again

	//return true if successful
	if (!skipEmptySpace(input, i)) {
		return false;
	}

	while (input.at(i) != ' ') { //pick out individual words
		current.push_back(input.at(i));
		i++; //move to next character or number

		if (i >= length) {
			break; //end of input
		}
	}

	y = stringToInt(current); //store the y position of player

	if (checkXY) {
		if ((x >= x_Size) || (y >= y_Size) || (x < 0) || (y < 0)) {
			cout << "X Y coordinate is out of range" << endl;
			return false;
		}
	}

	return true;
}

void roomClass::setupRoom(int x, int y) {
	matrix = new tileClass[x * y];
	setXSize(x);
	setYSize(y);
}

void roomClass::startLocation(int xStart, int yStart) {
	setXSize(xStart);
	setYSize(yStart);
}

bool roomClass::isExit(int x, int y) {
	if (matrix[player.getXYtoPos(x, y)].getElement() == ('E')) {
		return true;
	}
	return false;
}

bool roomClass::isWall(int x, int y) {
	if (matrix[player.getXYtoPos(x, y)].getElement() == ('*')) {
		return true;
	}
	return false;
}

bool roomClass::isChest(int x, int y) {
	if (matrix[player.getXYtoPos(x, y)].getElement() == ('C')) {
		return true;
	}
	return false;
}

bool roomClass::isDoor(int x, int y) {
	if (matrix[player.getXYtoPos(x, y)].getElement() == ('D')) {
		return true;
	}
	return false;
}

void roomClass::freeUpRoom() {
	delete[] matrix;
	/*for (int i = 0; i < (x_Size * y_Size); i++) {
		free(&matrix[i]);
	}
	free(matrix);*/
}

//testing purposes
void roomClass::printBoard() {
	for (int i = 0; i < x_Size * 2; i++) {
		cout << "_";
	}
	cout << endl;

	for (int i = 0; i < y_Size; i++) {
		cout << "|";
		for (int j = 0; j < x_Size; j++) {
			cout << matrix[player.getXYtoPos(j, i)].getElement() << " ";
		}
		cout << "|" << endl;
	}
	for (int i = 0; i < x_Size * 2; i++) {
		cout << "-";
	}
	cout << endl << endl;
}

