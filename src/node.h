#pragma once

#include <vector>
#include <memory>

class Node
{
public:
	Node(int value);

	std::shared_ptr<std::vector<Node>> next_nodes;
	int value;
	int count;
};