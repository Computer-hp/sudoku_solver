#pragma once

#include "node.h"
#include <vector>

class Graph
{
public:
	Graph();
	~Graph() = default;

	void store_permutations(const std::vector<std::vector<int>> &permutations);
	void print_nodes();

	std::vector<Node> nodes;

private:
	void insert_permutation(std::vector<Node> *nodes, 
							const std::vector<int> &permutation, long unsigned int i);
	void print_helper(int value, const std::shared_ptr<std::vector<Node>> nodes);
};