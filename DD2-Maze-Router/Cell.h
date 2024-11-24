#pragma once
#include <iostream>
#include "CellType.h"

using namespace std;

class Cell {
public:

    // Constructor
    Cell(int x, int y, int z, cell_type type);
    Cell();

    // Destructor
    ~Cell();

	// Getter for x
	int getX() const;

	// Setter for x
	void setX(int x);

	// Getter for y
	int getY() const;

	// Setter for y
	void setY(int y);

	// Getter for z
	int getZ() const;

	// Setter for z
	void setZ(int z);

    // Getter for cost
    int getCost() const;

    // Setter for cost
    void setCost(int cost);

    // Getter for type
    cell_type getType() const;

    // Setter for type
    void setType(cell_type type);

    bool operator>(Cell const& rhs);


private:
    int x;
    int y;
	int z;
    int cost;
    cell_type type;
};