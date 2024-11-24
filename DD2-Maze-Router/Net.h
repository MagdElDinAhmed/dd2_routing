#pragma once

#include <iostream>
#include <vector>
#include "Cell.h"
#include "CellType.h"

using namespace std;

class Net {
public:
    // Constructor
    Net(int net_id);

    // Destructor
    ~Net();

    // Getter for net_id
    int getNetId();

    // Setter for net_id
    void setNetId(int net_id);

	// Getter for pins
	vector<vector<int>> getPins();

	// Setter for pins
	void setPins(vector<vector<int>> pins);

	// Add pin
	void addPin(vector<int> pin);

	// Print pins
	void printPins();

	// Getter for path
	vector<vector<int>> getPath();

	// Add path
	void setPath(vector<vector<int>> path);

private:
    int net_id;
    vector<vector<int>> pins;
	vector<vector<int>> path;

};