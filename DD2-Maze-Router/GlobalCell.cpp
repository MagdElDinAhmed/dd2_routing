#include <iostream>
#include "GlobalCell.h"

using namespace std;

// Constructor
GlobalCell::GlobalCell(int cap) : capacity(cap) {}

// Getter for capacity
int GlobalCell::getCapacity() {
    return capacity;
}

// Setter for capacity
void GlobalCell::setCapacity(int cap) {
    capacity = cap;
}