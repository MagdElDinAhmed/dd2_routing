#include "Router.h"
#include <climits>
bool Router::route(Net& net, std::vector<std::vector<std::vector<Cell>>>& grid, int bend, int via)
{
    // Get width and length
    width = grid[0].size();
    length = grid[0][0].size();
    this->grid = &grid; // Point to the original grid
    bendPenality = bend;
    viaPenality = via;
    this->net = &net;

    // Loop over the pins in the net, setting their type correctly in the grid
    std::vector<std::vector<int>> pins = net.getPins();
    for (size_t i = 0; i < pins.size(); i++) {
        const std::vector<int>& currentPin = pins[i];
        Cell& currentCell = (*this->grid)[currentPin[0]][currentPin[2]][currentPin[1]];
        currentCell.setType(TARGET);
    }

    //If there is only one pin set it as source and add it to the list
    if (pins.size() >= 1) {
        const std::vector<int>& sourceStart = pins[0];
        Cell& source_cell = (*this->grid)[sourceStart[0]][sourceStart[2]][sourceStart[1]];
        source_cell.setType(SOURCE);
        result.insert(result.begin(), sourceStart);
    }
    // Loop over each pin, connecting it to the network
    for (size_t i = 1; i < pins.size(); i++) {
        const std::vector<int>& target = pins[i];
        Cell& source_cell = (*this->grid)[target[0]][target[2]][target[1]];
        if (source_cell.getType() != SOURCE) {
            std::vector<int> source = findClosestSource(target);
            if (source[0] == -1)
                return false;
            if (!retraceToTarget(source))
                return false;
            cleanUpAfterOneRoute();
        }
    }

    // Print the result and cleanup
    printResult();
    cleanUpAfterAllRoutes();
    return true;
}

std::vector<int> Router::findClosestSource(std::vector<int> target){
    std::vector<std::vector<std::vector<bool>>> visited(2, std::vector<std::vector<bool>>(width, std::vector<bool>(length, false)));
    (*this->grid)[target[0]][target[2]][target[1]].setCost(0);
    int vertices = 2 * width * length;
    for(int counter = 0; counter < vertices; counter++) {
        std::vector<int> currentNode = minDist(visited);
        visited[currentNode[0]][currentNode[2]][currentNode[1]] = true;
        Cell& currentCell = (*this->grid)[currentNode[0]][currentNode[2]][currentNode[1]];

        std::vector<std::vector<int>> adj_nodes = getAdjacentNodes(currentNode);

        for (const auto& adj_node : adj_nodes) {
            if (isValidNode(adj_node)) {
                Cell& adj_cell = (*this->grid)[adj_node[0]][adj_node[2]][adj_node[1]];
                int cost = (currentCell.getCost() == INT_MAX) ? INT_MAX : currentCell.getCost() + getMoveCost(currentNode, adj_node);

                if (!visited[adj_node[0]][adj_node[2]][adj_node[1]] &&
                    adj_cell.getCost() > cost && adj_cell.getType() != OBSTACLE) {
                    adj_cell.setCost(cost);
                }
            }
        }
    }

    int min_cost = INT_MAX;
    vector<int> min_node;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            for (int z = 0; z < 2; z++) {
                if ((*this->grid)[z][i][j].getCost() < min_cost && (*this->grid)[z][i][j].getType() == SOURCE) {
                    min_cost = (*this->grid)[z][i][j].getCost();
                    min_node = { z,j,i };
                }
            }
        }
    }

    if (min_cost == INT_MAX) {
        return { -1 };
    }
    else {
        return min_node;
    }
}

std::vector<std::vector<int>> Router::getAdjacentNodes(const std::vector<int>& node)
{
    std::vector<std::vector<int>> adj_nodes;

    if (node[0] == 0 || node[0] == 1) {
        // Nodes in the same layer
        std::vector<int> directions = { -1, 1 };
        for (int d : directions) {
            // Horizontal movement
            std::vector<int> adj_node = node;
            adj_node[1] += d;
            adj_nodes.push_back(adj_node);

            // Vertical movement
            adj_node = node;
            adj_node[2] += d;
            adj_nodes.push_back(adj_node);
        }

        // Via movement
        std::vector<int> adj_node = node;
        adj_node[0] = 1 - node[0]; // Switch layer
        adj_nodes.push_back(adj_node);
    }
    return adj_nodes;
}

int Router::getMoveCost(const std::vector<int>& fromNode, const std::vector<int>& toNode)
{
    if (fromNode[0] != toNode[0]) {
        return viaPenality; // Moving between layers
    } else if ( (fromNode[0] == 0 && fromNode[2] != toNode[2]) || (fromNode[0] == 1 && fromNode[1] != toNode[1])) {
        return bendPenality; // Changing direction (bend)
    } else {
        return 1; // Straight movement
    }
}

bool Router::isValidNode(const std::vector<int>& node) const {
    return node[0] >= 0 && node[0] < grid->size() &&
           node[2] >= 0 && node[2] < (*grid)[0].size() &&
           node[1] >= 0 && node[1] < (*grid)[0][0].size();
}

bool Router::retraceToTarget(std::vector<int> source)
{
    std::vector<int> currentNode = source;
    Cell& currentCell = (*this->grid)[currentNode[0]][currentNode[2]][currentNode[1]];
    while (currentCell.getType() != TARGET) {
        currentCell.setType(SOURCE);

        std::vector<std::vector<int>> adj_nodes = getAdjacentNodes(currentNode);
        int min_cost = INT_MAX;
        std::vector<int> selected = currentNode;

        for (const auto& adj_node : adj_nodes) {
            if (isValidNode(adj_node)) {
                Cell& adj_cell = (*this->grid)[adj_node[0]][adj_node[2]][adj_node[1]];
                if (adj_cell.getCost() < min_cost && adj_cell.getType() != OBSTACLE) {
                    min_cost = adj_cell.getCost();
                    selected = adj_node;
                }
            }
        }

        if (selected == currentNode) {
            cout << "ERROR RETRACING STEPS, NO ROUTE EXIST\n";
            return false;
        }
        else {
            currentNode = selected;
            currentCell = (*this->grid)[currentNode[0]][currentNode[2]][currentNode[1]];
            result.insert(result.begin(), currentNode);
        }
    }
    (*this->grid)[currentNode[0]][currentNode[2]][currentNode[1]].setType(SOURCE);
    return true;
}

void Router::printResult()
{
    cout << "Net" << net->getNetId() << "\n";
    for (const auto& node : result) {
        std::cout << "(" << node[0] << "," << node[1] << "," << node[2] << ")\n";
    }
    net->setPath(result);
    result.erase(result.begin(), result.end());
}

void Router::cleanUpAfterAllRoutes()
{
    for (size_t i = 0; i < grid->size(); i++) {
        for (size_t j = 0; j < (*grid)[i].size(); j++) {
            for (size_t k = 0; k < (*grid)[i][j].size(); k++) {
                Cell& current_Cell = (*grid)[i][j][k];
                current_Cell.setCost(INT_MAX);
                if (current_Cell.getType() == SOURCE)
                    current_Cell.setType(OBSTACLE);
            }
        }
    }
}

void Router::cleanUpAfterOneRoute()
{
    for (size_t i = 0; i < grid->size(); i++) {
        for (size_t j = 0; j < (*grid)[i].size(); j++) {
            for (size_t k = 0; k < (*grid)[i][j].size(); k++) {
                Cell& current_Cell = (*grid)[i][j][k];
                current_Cell.setCost(INT_MAX);
            }
        }
    }
}

vector<int> Router::minDist(std::vector<std::vector<std::vector<bool>>> visited) {
    int min_cost = INT_MAX;
    vector<int> min_node;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            for (int z = 0; z < 2; z++) {
                if (!visited[z][i][j] && (*this->grid)[z][i][j].getCost() <= min_cost) {
                    min_cost = (*this->grid)[z][i][j].getCost();
                    min_node = { z,j,i };
                }
            }
        }
    }

    return min_node;
}

