#ifndef NETS_H
#define NETS_H

#include <iostream>
#include <vector>
#include "Cell.h"
#include "CellType.h"

using namespace std;

class Nets {
public:
    // Constructor
    Nets(int net_id, int num_pins);

    // Destructor
    ~Nets() {}

    // Getter for net_id
    int getNetId();

    // Setter for net_id
    void setNetId(int net_id);

    // Getter for num_pins
    int getNumPins();

    // Setter for num_pins
    void setNumPins(int num_pins);

private:
    int net_id;
    int num_pins;
    vector<Cell> pins;

};
#endif // NETS_H