#include <iostream>
#include <string>
#include "TextParser.h"
#include "Cell.h"
#include "CellType.h"
#include "Nets.h"

using namespace std;

// Helper function to remove trailing and beginning whitespaces
string trim(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first) {
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

// Helper function to check if a string is a valid integer
bool isValidInteger(const string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

// Helper function to check if data is valid
bool isValidData(const vector<int>& data, const vector<vector<vector<Cell>>>& detailed_grid) {
	
	bool valid = true;
	
	if (data[0] > 1 || data[0] < 0)
	{
		cout << "Invalid metal layer" << endl;
		valid = false;
	}
	else if (data[1] >= detailed_grid[0][0].size() || data[1] < 0)
	{
		cout << "Invalid column number" << endl;
		valid = false;
	}
	else if (data[2] >= detailed_grid[0].size() || data[2] < 0)
	{
		cout << "Invalid row number" << endl;
		valid = false;
	}
	else if (data.size() < 3)
	{
		cout << "Too few arguments for placement" << endl;
		valid = false;
	}
	else if (data.size() > 3)
	{
		cout << "Too many arguments for placement" << endl;
		valid = false;
	}
	else if (detailed_grid[data[0]][data[2]][data[1]].getType() != EMPTY)
	{
		cout << "Space is already occupied" << endl;
		valid = false;
	}

	return valid;
}

// Constructor
TextParser::TextParser(string filename) : filename(filename) {}

// Destructor
TextParser::~TextParser() {}

// Getter for filename
string TextParser::getFilename() {
    return filename;
}

// Setter for filename
void TextParser::setFilename(string filename) {
    this->filename = filename;
}

// Parse first line
vector<int> TextParser::parseFirstLine(string line, bool &success) {
    stringstream ss(line);
    string word;
    vector<int> numbers;
    while (getline(ss, word, ',')) {
        
		if (!isValidInteger(trim(word)) || numbers.size() >= 4) {
			cout << "Invalid first line data" << endl;
			success = false;
			return numbers;
		}
        
        int number = stoi(word);
        numbers.push_back(number);
    }
	for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << endl;
	}
    return numbers;
}

// Parse lines
bool TextParser::parseLine(string line, vector<vector<vector<Cell>>> &detailed_grid, vector<Nets> &nets) {
    stringstream ss(line);
    string word;
    ss >> word;
	// Handle different cases
	
    if (word == "OBS") {
        // Handle case for obstacle
        stringstream ss(line);
        string temp;
        vector<int> cellData;

        // Get the coordinates of the obstacle
        size_t pos = line.find('(');
        if (pos != string::npos) {
            temp = line.substr(pos + 1); // Get the substring after '('
            size_t endPos = temp.find(')');
            if (endPos != string::npos) {
                temp = temp.substr(0, endPos); // Remove the part after ')'
            }
            stringstream ss(temp);
            while (getline(ss, temp, ',')) {
				
                if (!isValidInteger(trim(temp))) {
					cout << "Invalid obstacle data" << endl;
					return false;
				}
                cellData.push_back(stoi(temp));
                cout << temp << endl;
            }
        }

		if (isValidData(cellData, detailed_grid)) {
			detailed_grid[cellData[0]][cellData[2]][cellData[1]].setType(OBSTACLE);
		}
		else
		{
			return false;
		}

    } else if (word.substr(0, 3) == "net") {
        // Handle net case
		nets.push_back(Nets(stoi(word.substr(3))));
        stringstream ss(line);
        string temp;
        vector<int> netData;

		// Get the coordinates of the pins
        while (getline(ss, temp, '(')) {
			netData.clear();
            if (getline(ss, temp, ')')) {
                stringstream coordStream(temp);
                string coord;
                while (getline(coordStream, coord, ',')) {
					if (!isValidInteger(trim(coord))) {
						cout << "Pin coordinates must be a number" << endl;
						return false;
					}
                    netData.push_back(stoi(coord));
                }

				if (isValidData(netData, detailed_grid)) {
					nets[nets.size() - 1].addPin(netData);
					detailed_grid[netData[0]][netData[2]][netData[1]].setType(PIN);
				}
				else
				{
					return false;
				}

            }
        }
    }

	return true;
}

// Read file
bool TextParser::readFile(int& bend_penalty, int& via_penalty, vector<vector<vector<Cell>>> &detailed_grid, vector<Nets> &nets) {
	cout << "Reading file: " << filename << endl;
    ifstream file(filename);
    string line;

	bool success = true;

    if (file.is_open()) {
        string first_line;
        getline(file, first_line);

        
        vector<int> first_line_numbers = parseFirstLine(first_line, success);

        if (success) {
            // Initialize each cell as EMPTY
            for (int z = 0; z < 2; z++) {
                for (int y = 0; y < first_line_numbers[1]; y++) {
                    detailed_grid[z].push_back(vector<Cell>());
                    for (int x = 0; x < first_line_numbers[0]; x++) {
                        detailed_grid[z][y].push_back(Cell(EMPTY));
                    }
                }
            }

            bend_penalty = first_line_numbers[2];
            via_penalty = first_line_numbers[3];

            while (success && getline(file, line)) {
                success = parseLine(line, detailed_grid, nets);
            }
        }

        
        file.close();
    } else {
        cout << "Unable to open file" << endl;
        success = false;
    }

	return success;
}
