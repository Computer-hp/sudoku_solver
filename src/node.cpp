#include "node.h"

Node::Node(int value)
{
	this->value = value;
	next_nodes = std::make_shared<std::vector<Node>>();
	count = 0;
}