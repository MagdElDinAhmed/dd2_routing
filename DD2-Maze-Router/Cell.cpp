#include <iostream>
#include "Cell.h"
#include "CellType.h"

using namespace std;

// Constructor
Cell::Cell(int x, int y, int z, cell_type type) : x(x), y(y), z(z), type(type), cost(INT_MAX) {}

// Destructor
Cell::~Cell() {}

// Getter for x
int Cell::getX() const {
	return x;
}

// Setter for x
void Cell::setX(int x) {
	this->x = x;
}

// Getter for y
int Cell::getY() const {
	return y;
}

// Setter for y
void Cell::setY(int y) {
	this->y = y;
}

// Getter for z
int Cell::getZ() const {
	return z;
}

// Setter for z
void Cell::setZ(int z) {
	this->z = z;
}

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

bool Cell::operator>(Cell const& rhs)
{
    return getCost() > rhs.getCost();
}
