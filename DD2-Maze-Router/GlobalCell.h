#pragma once
#include <iostream>
#include "Cell.h"

class GlobalCell : public Cell {
public:
    // Constructor
    GlobalCell(cell_type type, int capacity);

    // Destructor
    ~GlobalCell();

    // Getter for global cost
    int getCapacity() const;

    // Setter for global cost
    void setCapacity(int capacity);

private:
    int capacity;
};
