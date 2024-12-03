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

// Getter for path cost
int Net::getPathCost() {
	return path_cost;
}

// Setter for path cost
void Net::setPathCost() {
	path_cost = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		path_cost += abs(path[i][0] - path[i + 1][0]) + abs(path[i][1] - path[i + 1][1]) + abs(path[i][2] - path[i + 1][2]);
	}
}

// Getter for via count
int Net::getViaCount() {
	return via_count;
}

// Setter for via count
void Net::setViaCount() {
	via_count = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		if (path[i][0] != path[i + 1][0]) {
			via_count++;
		}
	}
}