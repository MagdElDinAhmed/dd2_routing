#include <iostream>
#include <string>
#include "TextParser.h"
#include "Cell.h"
#include "CellType.h"
#include "Nets.h"

using namespace std;

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
vector<int> TextParser::parseFirstLine(string line) {
    stringstream ss(line);
    string word;
    vector<int> numbers;
    int count = 0;
    while (getline(ss, word, ',') && count < 4) {
        int number = stoi(word);
        numbers.push_back(number);
        count++;
    }
	for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << endl;
	}
    return numbers;
}

// Parse lines
void TextParser::parseLine(string line, vector<vector<vector<Cell>>> &detailed_grid, vector<Nets> &nets) {
    stringstream ss(line);
    string word;
    ss >> word;
	// Handle different cases
	// Handle case for obstacle
    if (word == "OBS") {
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
                cellData.push_back(stoi(temp));
                cout << temp << endl;
            }
        }

		// If the cell data is complete, set the cell type to OBSTACLE
        if (cellData.size() == 3 && detailed_grid[cellData[0]][cellData[1]][cellData[2]].getType()== EMPTY) {
			detailed_grid[cellData[0]][cellData[1]][cellData[2]].setType(OBSTACLE);
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
                    netData.push_back(stoi(coord));
                }
                if (netData.size() == 3 && detailed_grid[netData[0]][netData[1]][netData[2]].getType() == EMPTY) {
                    nets[nets.size() - 1].addPin(netData);
					detailed_grid[netData[0]][netData[1]][netData[2]].setType(PIN);
                }
            }
        }
    }
}

// Read file
void TextParser::readFile(int& bend_penalty, int& via_penalty, vector<vector<vector<Cell>>> &detailed_grid, vector<Nets> &nets) {
	cout << "Reading file: " << filename << endl;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        string first_line;
        getline(file, first_line);
        vector<int> first_line_numbers = parseFirstLine(first_line);

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


        while (getline(file, line)) {
            parseLine(line, detailed_grid, nets);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}
