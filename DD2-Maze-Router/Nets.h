#pragma once

#include <iostream>
#include <vector>
#include "Cell.h"
#include "CellType.h"

using namespace std;

class Nets {
public:
    // Constructor
    Nets(int net_id);

    // Destructor
    ~Nets();

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

private:
    int net_id;
    vector<vector<int>> pins;

};