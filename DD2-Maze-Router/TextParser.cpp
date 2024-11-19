#include <iostream>
#include <string>
#include "TextParser.h"
#include "Cell.h"

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
    return numbers;
}

// Parse lines
void TextParser::parseLine(string line) {
    stringstream ss(line);
    string word;
    ss >> word;
    if (word == "OBS") {
        stringstream ss(line);
        string temp;
        vector<int> cellData;
        while (getline(ss, temp, ',')) {
            cellData.push_back(stoi(temp));
        }
        if (cellData.size() >= 3) {
            Cell cell(cellData[0], cellData[1], cellData[2], OBSTACLE);
            cells.push_back(cell);
        }
    } else if (word == "net") {
        
    }
}

// Read file
void TextParser::readFile() {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        string first_line;
        getline(file, first_line);
        vector<int> first_line_numbers = parseFirstLine(first_line);

        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}
