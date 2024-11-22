#pragma once

class GlobalCell {
public:
    // Constructor
    GlobalCell(int cap);

    // Getter for capacity
    int getCapacity();

    // Setter for capacity
    void setCapacity(int cap);

private:
    int capacity;
};
