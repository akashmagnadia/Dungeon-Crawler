#include "amagna2Proj7.h"
//

int main(int argc, char** argv)
{
	bool debugMode = true;
	// set up the variable inFile to read from standard input
	
	string inFile = "";
	if (argc < 2) {
		cout << "File Not Entered" << endl;
		return 1;
	}
	else {
		cout << argv[1] << endl;
		inFile = argv[1];
	}

	roomClass room;

	room.showCommands(); //show commands

	room.processCommandLoop(inFile); //processCommandLoop

	room.printBoard();

	//clean up
	return 1;
}
