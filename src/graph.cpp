#include "graph.h"
#include <iostream>

Graph::Graph()
{ 
	nodes = {};
}


void Graph::store_permutations(const std::vector<std::vector<int>> &permutations)
{
	for (long unsigned int i = 0; i < permutations.size(); ++i)
		insert_permutation(&nodes, permutations[i], 0);
}


void Graph::insert_permutation(std::vector<Node> *nodes, 
							   const std::vector<int> &permutation, long unsigned int i)
{
	if (i == permutation.size()) return;

	long int value_pos = -1;
	for (long unsigned int j = 0; j < nodes->size(); ++j)
	{
		if (nodes->size() <= 0) break;

		if ((*nodes)[j].value == permutation[i]) 
		{
			value_pos = j;
			break;
		}
	}

	if (value_pos == -1) 
	{
		(*nodes).push_back(Node(permutation[i]));
		insert_permutation((*nodes).back().next_nodes.get(), permutation, i + 1);
	}
	else
		insert_permutation((*nodes)[value_pos].next_nodes.get(), permutation, i + 1);
}


void Graph::print_nodes()
{
	for (long unsigned int i = 0; i < nodes.size(); ++i)	
	{
		print_helper(nodes[i].value, nodes[i].next_nodes);
		std::cout << '\n';
	}
}


void Graph::print_helper(int value, const std::shared_ptr<std::vector<Node>> nodes)
{
	std::cout << value << ' ';

	if (nodes->size() == 0) return;

	else print_helper((*nodes)[0].value, (*nodes)[0].next_nodes);
}