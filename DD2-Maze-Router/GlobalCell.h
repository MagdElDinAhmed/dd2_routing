#ifndef GLOBALCELL_H
#define GLOBALCELL_H

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

#endif // GLOBALCELL_H