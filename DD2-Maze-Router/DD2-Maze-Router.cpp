// DD2-Maze-Router.cpp : Defines the entry point for the application.
//

#include "DD2-Maze-Router.h"
#include "TextParser.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// Initialize variables
	vector<vector<vector<Cell>>> detailed_grid;
	vector<Nets> nets;
	detailed_grid.resize(2);
	int bend_penalty, via_penalty;
	TextParser tp("test.txt");
	
	// Read file
	cout << tp.getFilename() << endl;
	if (tp.readFile(bend_penalty, via_penalty, detailed_grid, nets))
	{
		for (int i = 0; i < nets.size(); i++) {
			cout << "Net " << nets[i].getNetId() << endl;
			nets[i].printPins();
		}
	}
	else
	{
		cout << "Failed to read file" << endl;
	}

	
	return 0;
}
