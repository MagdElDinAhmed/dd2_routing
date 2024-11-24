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
	vector<Net> nets;
	detailed_grid.resize(2);
	int bend_penalty, via_penalty;
	TextParser tp("test_1.txt");
	
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

	Router r;
	for (int i = 0; i < nets.size(); i++) {
		r.route(nets.at(i), detailed_grid, bend_penalty, via_penalty);
	}

	// Open file for writing
	ofstream outfile("routed_nets.txt");
	if (!outfile.is_open()) {
		cerr << "Failed to open file for writing" << endl;
		return 1;
	}

	// Print the path for each net to the file
	for (Net& net : nets) {
		outfile << "net" << net.getNetId();
		const auto& path = net.getPath();
		for (const auto& node : path) {
			outfile << " (" << node[0] << "," << node[1] << "," << node[2] << ")";
		}
		outfile << endl;
	}

	// Close the file
	outfile.close();
	
	return 0;
}
