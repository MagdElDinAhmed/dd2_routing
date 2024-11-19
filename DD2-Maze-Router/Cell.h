#ifndef CELL_H
#define CELL_H
#include <iostream>
#include "CellType.h"

using namespace std;

class Cell {
public:

    // Constructor
    Cell(int layer, int x, int y, cell_type type);

    // Destructor
    ~Cell() {}

    // Getter for layer
    int getLayer() const;

    // Setter for layer
    void setLayer(int layer);

    // Getter for x
    int getX() const;

    // Setter for x
    void setX(int x);

    // Getter for y
    int getY() const;

    // Setter for y
    void setY(int y);

    // Getter for cost
    int getCost() const;

    // Setter for cost
    void setCost(int cost);

    // Getter for type
    cell_type getType() const;

    // Setter for type
    void setType(cell_type type);

    // Overload operator==
    bool operator==(const Cell& other) const;


private:
    int layer;
    int x;
    int y;
    int cost;
    cell_type type;
};

#endif // COORDINATES_H