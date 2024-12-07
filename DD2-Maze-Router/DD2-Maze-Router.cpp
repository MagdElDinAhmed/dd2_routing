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

	// Set the lengths of the paths and count the number of vias
	for (Net& net : nets) {
		net.setPathCost();
		net.setViaCount();
	}

	// Display the longest route
	int longest_route = 0;
	for (Net& net : nets) {
		if (net.getPath().size() > longest_route) {
			longest_route = net.getPath().size();
		}
	}

	cout << "Longest route: " << longest_route << endl;

	// Get total wire length
	int total_wire_length = 0;
	for (Net& net : nets) {
		total_wire_length += net.getPathCost();
	}

	cout << "Total wire length: " << total_wire_length << endl;

	// Get total number of vias
	int total_vias = 0;
	for (Net& net : nets) {
		total_vias += net.getViaCount();
	}

	cout << "Total vias: " << total_vias << endl;

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
