#pragma once
#ifndef ROUTER
#define ROUTER

#include "Net.h"
#include "Cell.h"
#include <vector>
#include <stack>
#include <queue>

class Router
{
public:
    bool route(Net& net, std::vector<std::vector<std::vector<Cell>>>& grid, int bend, int via);
    std::vector<std::vector<std::vector<Cell>>>* grid; // Pointer to grid

private:
    std::vector<int> findClosestTarget(std::vector<int> target);
    std::vector<std::vector<int>> getAdjacentNodes(const std::vector<int>& node);
    int getMoveCost(const std::vector<int>& fromNode, const std::vector<int>& toNode);
    bool isValidNode(const std::vector<int>& node) const;
    void retraceToSource(std::vector<int> source);
    void printResult();
    void cleanUpAfterAllRoutes();

    int bendPenality, viaPenality;
    std::vector<std::vector<int>> result;
    size_t length, width; // Changed to size_t
};

// Node Comparator for sorting
struct comp {
    Router* router; // Pointer to Router instance
    comp(Router* r) : router(r) {}

    bool operator()(const std::vector<int>& node1, const std::vector<int>& node2) const {
        // Access the grid directly
        const Cell& a1 = (*router->grid)[node1[0]][node1[1]][node1[2]];
        const Cell& a2 = (*router->grid)[node2[0]][node2[1]][node2[2]];
        return a1.getCost() > a2.getCost(); // Compare based on cost
    }
};

#endif // !ROUTER

