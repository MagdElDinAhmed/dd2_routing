#include "Router.h"

vector<vector<vector<Cell>>> Router::grid = vector<vector<vector<Cell>>>();

bool Router::route(Net net, vector<vector<vector<Cell>>>& grid, int bend, int via)
{
	//get width and length
	width = grid[0].size();
	length = grid[0][0].size();
	this->grid = grid;
	bendPenality = bend;
	viaPenality = via;

	//loop over the pins in the net setting their type correctly in the grid
	vector<vector<int>> pins = net.getPins();
	for (int i = 0; i < pins.size(); i++) {
		vector<int> currentPin = pins[i];
		Cell cell;
		getCellFromNode(currentPin, cell);
		cell.setType(SOURCE);
	}

	//Loop over each pin connecting it to the network
	for (int i = 0; i < pins.size(); i++) {
		vector<int> target = pins[i];
		Cell tarCell;
		getCellFromNode(target, tarCell);
		tarCell.setType(TARGET);
		vector<int> source = findClosestSource(target);
		if (source.at(0) == -1)
			return false;
		retraceToTarget(source);
	}

	//Print the result and cleanup
	printResult();
	cleanUpAfterAllRoutes();
	return true;
}

vector<int> Router::findClosestSource(vector<int> target)
{
	priority_queue<vector<int>, vector<vector<int>>, comp> nodeQueue;
	//vector<vector<vector<bool>>> visited(2, vector<vector<bool>>(width, vector<bool>(length, false)));
	nodeQueue.push(target);
	//visited[target[0]][target[1]][target[2]] = true;
	Cell targetCell;
	getCellFromNode(target, targetCell);
	targetCell.setCost(0);
	while (!nodeQueue.empty()) {
		vector<int> currentNode = nodeQueue.top();
		nodeQueue.pop();
		Cell currentCell;
		getCellFromNode(currentNode, currentCell);
		if (currentCell.getType() == SOURCE)
			return currentNode;
		if (currentNode.at(0) == 0) {
			vector<int> adj_node = currentNode;

			//node on top
			adj_node.at(0) = 1;
			Cell adj_cell;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + viaPenality && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + viaPenality);
				nodeQueue.push(adj_node);
			}

			//node to the right
			adj_node.at(0) = 0;
			adj_node.at(1) = adj_node.at(1) + 1;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + 1 && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + 1);
				nodeQueue.push(adj_node);
			}

			//node to the left
			adj_node.at(1) = adj_node.at(1) - 2;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + 1 && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + 1);
				nodeQueue.push(adj_node);
			}

			//node forward
			adj_node.at(1) = adj_node.at(1) + 1;
			adj_node.at(2) = adj_node.at(2) + 1;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + bendPenality && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + bendPenality);
				nodeQueue.push(adj_node);
			}

			//node backward
			adj_node.at(2) = adj_node.at(2) - 2;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + bendPenality && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + bendPenality);
				nodeQueue.push(adj_node);
			}
		}
		else if (currentNode.at(0) != NULL && currentNode.at(0) == 1) {
			vector<int> adj_node = currentNode;

			//node below
			adj_node.at(0) = 0;
			Cell adj_cell;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + viaPenality && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + viaPenality);
				nodeQueue.push(adj_node);
			}

			//node to the right
			adj_node.at(0) = 1;
			adj_node.at(1) = adj_node.at(1) + 1;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + bendPenality && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + bendPenality);
				nodeQueue.push(adj_node);
			}

			//node to the left
			adj_node.at(1) = adj_node.at(1) - 2;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + bendPenality && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + bendPenality);
				nodeQueue.push(adj_node);
			}

			//node forward
			adj_node.at(1) = adj_node.at(1) + 1;
			adj_node.at(2) = adj_node.at(2) + 1;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + 1 && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + 1);
				nodeQueue.push(adj_node);
			}

			//node backward
			adj_node.at(2) = adj_node.at(2) - 2;
			getCellFromNode(adj_node, adj_cell);
			if (adj_cell.getCost() > currentCell.getCost() + 1 && adj_cell.getType() != OBSTACLE) {
				adj_cell.setCost(currentCell.getCost() + 1);
				nodeQueue.push(adj_node);
			}
		}
	}
	vector<int> result = { -1 };
	return result;

}

void Router::retraceToTarget(vector<int> source)
{
	vector<int> currentNode = source;
	vector<int> selected = currentNode;
	Cell currentCell;
	getCellFromNode(currentNode, currentCell);
	while (currentCell.getType() != TARGET) {
		result.push_back(currentNode);
		Cell adj_cell;
		getCellFromNode(currentNode, adj_cell);
		adj_cell.setType(SOURCE);
		vector<int> adj_node = currentNode;
		selected = currentNode;

		//search for next node smallest node in cost
		int min_cost = INT32_MAX;

		adj_node.at(1) = adj_node.at(1) + 1;
		getCellFromNode(adj_node, adj_cell);
		if (adj_cell.getCost() < min_cost && adj_cell.getType() != OBSTACLE) {
			min_cost = adj_cell.getCost();
			selected = adj_node;
		}

		adj_node.at(1) = adj_node.at(1) - 2;
		getCellFromNode(adj_node, adj_cell);
		if (adj_cell.getCost() < min_cost && adj_cell.getType() != OBSTACLE) {
			min_cost = adj_cell.getCost();
			selected = adj_node;
		}

		adj_node.at(1) = adj_node.at(1) + 1;
		adj_node.at(2) = adj_node.at(2) + 1;
		getCellFromNode(adj_node, adj_cell);
		if (adj_cell.getCost() < min_cost && adj_cell.getType() != OBSTACLE) {
			min_cost = adj_cell.getCost();
			selected = adj_node;
		}

		adj_node.at(2) = adj_node.at(2) - 2;
		getCellFromNode(adj_node, adj_cell);
		if (adj_cell.getCost() < min_cost && adj_cell.getType() != OBSTACLE) {
			min_cost = adj_cell.getCost();
			selected = adj_node;
		}

		adj_node.at(2) = adj_node.at(2) + 1;
		if (adj_node.at(0) == 0)
			adj_node.at(0) = 1;
		else
			adj_node.at(0) = 0;
		getCellFromNode(adj_node, adj_cell);
		if (adj_cell.getCost() < min_cost && adj_cell.getType() != OBSTACLE) {
			min_cost = adj_cell.getCost();
			selected = adj_node;
		}

		if (selected == currentNode)
			break;
		else {
			currentNode = selected;
			getCellFromNode(currentNode, currentCell);
		}
	}
	result.push_back(currentNode);
	getCellFromNode(currentNode, currentCell);
	currentCell.setType(SOURCE);
}

void Router::printResult()
{
	for (int i = 0; i < result.size(); i++) {
		cout << "(" << result.at(i).at(0) << "," << result.at(i).at(1) << "," << result.at(i).at(2) << ")\n";
	}
}

void Router::cleanUpAfterAllRoutes()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			vector<int> current_node = { 0,i,j };
			Cell current_Cell;
			getCellFromNode(current_node, current_Cell);
			if (current_Cell.getType() == SOURCE)
				current_Cell.setType(OBSTACLE);
			current_node = { 1,i,j };
			getCellFromNode(current_node, current_Cell);
			if (current_Cell.getType() == SOURCE)
				current_Cell.setType(OBSTACLE);
		}
	}
}

void Router::getCellFromNode(vector<int> node, Cell &cell)
{
	if (node[0] != 1 && node[0] != 0)
		cell = Cell(OBSTACLE);
	else if (node[0] >= grid.size() || node[2] >= grid[node[0]].size() || node[1] >= grid[node[0]][node[2]].size())
		cell = Cell(OBSTACLE);
	else
		cell = grid[node[0]][node[2]][node[1]];
}

//int Router::calcHeuristicVal(vector<int> node1, vector<int> node2)
//{
//	if (node1.at(0) == node2.at(0)) {
//		if (node1.at(0) == 0)
//			return abs(node1.at(1) - node2.at(1)) + bendPenality * abs(node1.at(2) - node2.at(2));
//		else
//			return (bendPenality * abs(node1.at(1) - node2.at(1))) + abs(node1.at(2) - node2.at(2));
//	}
//	else {
//		return abs(node1.at(1) - node2.at(1)) + abs(node1.at(2) - node2.at(2)) + viaPenality;
//	}
//}
