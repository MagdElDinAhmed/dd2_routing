#pragma once
#ifndef ROUTER
#define ROUTER

#include "Net.h"
#include "Cell.h"
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Router
{
public:
	bool route(Net net, vector<vector<vector<Cell>>> &grid, int bend, int via);
	static void getCellFromNode(vector<int> node, Cell &cell);
	static vector<vector<vector<Cell>>> grid;

private:
	vector<int> findClosestSource(vector<int> target);
	void retraceToTarget(vector<int> source);
	void printResult();
	void cleanUpAfterAllRoutes();
	//int calcHeuristicVal(vector<int> node1, vector<int> node2);

	int bendPenality, viaPenality;
	vector<vector<int>> result;
	int length, width;
};

//Node Comparator for sorting
struct comp {
	bool operator()(vector<int> node1, vector<int> node2) {
		Cell a1;
		Router::getCellFromNode(node1, a1);
		Cell a2;
		Router::getCellFromNode(node2, a2);
		return a1 > a2;
	}
};

#endif // !ROUTER