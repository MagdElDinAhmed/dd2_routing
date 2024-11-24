#pragma once
#include <iostream>
#include "CellType.h"

using namespace std;

class Cell {
public:

    // Constructor
    Cell(cell_type type);
    Cell();

    // Destructor
    ~Cell();

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
    int cost;
    cell_type type;
};