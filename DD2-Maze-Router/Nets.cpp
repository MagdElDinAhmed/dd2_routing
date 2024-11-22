#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Nets.h"

using namespace std;

// Constructor
Nets::Nets(int net_id) : net_id(net_id) {}

// Destructor
Nets::~Nets() {}

// Getter for net_id
int Nets::getNetId() {
	return net_id;
}

// Setter for net_id
void Nets::setNetId(int net_id) {
	this->net_id = net_id;
}

// Getter for pins
vector<vector<int>> Nets::getPins() {
	return pins;
}

// Setter for pins
void Nets::setPins(vector<vector<int>> pins) {
	this->pins = pins;
}

// Add pin
void Nets::addPin(vector<int> pin) {
	pins.push_back(pin);
}

// Print pins
void Nets::printPins() {
	for (int i = 0; i < pins.size(); i++) {
		for (int j = 0; j < pins[i].size(); j++) {
			cout << pins[i][j] << " ";
		}
		cout << endl;
	}
}