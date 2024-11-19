#ifndef TEXTPARSER_H
#define TEXTPARSER_H

# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <algorithm>
# include "Cell.h"

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
	void readFile();

	// Parse lines
	void parseLine(string line);

	// Parse first line
	vector<int> parseFirstLine(string line);

private:
	string filename;
};

#endif // TEXTPARSER_H
