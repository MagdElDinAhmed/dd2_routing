#include <iostream>
#include "Cell.h"
#include "CellType.h"

using namespace std;

// Constructor
Cell::Cell(int layer, int x, int y, cell_type type) : layer(layer), x(x), y(y), type(type), cost(INT32_MAX) {}

// Getter for layer
int Cell::getLayer() const {
    return layer;
}

// Setter for layer
void Cell::setLayer(int layer) {
    this->layer = layer;
}

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

// Overload operator<<
ostream& operator<<(ostream& os, const Cell& coord) {
    os << "Layer: " << coord.getLayer() << ", X: " << coord.getX() << ", Y: " << coord.getY();
    return os;
}

// Overload operator==
bool Cell::operator==(const Cell& other) const {
    return (layer == other.layer && x == other.x && y == other.y);
}