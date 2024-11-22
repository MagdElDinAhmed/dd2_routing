#pragma once

# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <algorithm>
# include "Cell.h"
# include "Nets.h"

using namespace std;

class TextParser {
public:
	// Constructor
	TextParser(string filename);

	// Destructor
	~TextParser();

	// Getter for filename
	string getFilename();

	// Setter for filename
	void setFilename(string filename);

	// Read file
	void readFile(int &bend_penalty, int &via_penalty, vector<vector<vector<Cell>>> &detailed_grid, vector<Nets> &nets);

	// Parse lines
	void parseLine(string line, vector<vector<vector<Cell>>>& detailed_grid, vector<Nets>& nets);

	// Parse first line
	vector<int> parseFirstLine(string line);

private:
	string filename;
};
