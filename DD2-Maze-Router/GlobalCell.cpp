#include <iostream>
#include "GlobalCell.h"

using namespace std;

// Constructor
GlobalCell::GlobalCell(cell_type type, int globalCost) : Cell(type), capacity(capacity) {}

// Destructor
GlobalCell::~GlobalCell() {}

// Getter for global cost
int GlobalCell::getCapacity() const {
	return capacity;
}

// Setter for global cost
void GlobalCell::setCapacity(int capacity) {
	this->capacity = capacity;
}