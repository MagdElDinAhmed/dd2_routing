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

	// Take the name of the file as input
	string input_filename;
	cout << "Enter the name of the input file: ";
	cin >> input_filename;

	// Copy the contents of the input file to input.txt
	ifstream infile(input_filename);
	ofstream outfile("input.txt");

	if (!infile.is_open()) {
		cerr << "Failed to open input file" << endl;
		return 1;
	}

	if (!outfile.is_open()) {
		cerr << "Failed to open output file" << endl;
		return 1;
	}

	outfile << infile.rdbuf();

	infile.close();
	outfile.close();
	TextParser tp("input.txt");
	
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
		if (!r.route(nets.at(i), detailed_grid, bend_penalty, via_penalty)) {
			cout << "FAILED TO ROUTE, NO ROUTES EXIST\n";
			return 1;
		}
	}

	// Open file for writing
	ofstream outfile2("output.txt");
	if (!outfile2.is_open()) {
		cerr << "Failed to open file for writing" << endl;
		return 1;
	}

	// Print the path for each net to the file
	for (Net& net : nets) {
		outfile << "net" << net.getNetId();
		const auto& path = net.getPath();
		for (const auto& node : path) {
			int layer = node[0] + 1;
			outfile << " (" << layer << "," << node[1] << "," << node[2] << ")";
		}
		outfile << endl;
	}

	// Close the file
	outfile.close();
	
	return 0;
}
