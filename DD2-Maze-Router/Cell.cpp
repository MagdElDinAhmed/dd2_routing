#include <iostream>
#include "Cell.h"
#include "CellType.h"

using namespace std;

// Constructor
Cell::Cell(cell_type type) : type(type), cost(INT32_MAX) {}

// Destructor
Cell::~Cell() {}


// Getter for cost
int Cell::getCost() const {
    return cost;
}

// Setter for cost
void Cell::setCost(int cost) {
    this->cost = cost;
}

// Getter for type
cell_type Cell::getType() const {
    return type;
}

// Setter for type
void Cell::setType(cell_type type) {
    this->type = type;
}