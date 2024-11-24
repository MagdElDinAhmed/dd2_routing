#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Net.h"

using namespace std;

// Constructor
Net::Net(int net_id) : net_id(net_id) {}

// Destructor
Net::~Net() {}

// Getter for net_id
int Net::getNetId() {
	return net_id;
}

// Setter for net_id
void Net::setNetId(int net_id) {
	this->net_id = net_id;
}

// Getter for pins
vector<vector<int>> Net::getPins() {
	return pins;
}

// Setter for pins
void Net::setPins(vector<vector<int>> pins) {
	this->pins = pins;
}

// Add pin
void Net::addPin(vector<int> pin) {
	pins.push_back(pin);
}

// Getter for path
vector<vector<int>> Net::getPath() {
	return path;
}

// Setter for path
void Net::setPath(vector<vector<int>> path) {
	for (int i = 0; i < path.size(); i++) {
		this->path.push_back(vector<int>());
		for (int j = 0; j < path.at(i).size(); j++) {
			this->path.at(i).push_back(path.at(i).at(j));
		}
	}
}

// Print pins
void Net::printPins() {
	for (int i = 0; i < pins.size(); i++) {
		for (int j = 0; j < pins[i].size(); j++) {
			cout << pins[i][j] << " ";
		}
		cout << endl;
	}
}