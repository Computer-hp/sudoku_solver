#include "sudoku_solver.h"
#include <iostream>
#include <algorithm>

Sudoku_Solver::Sudoku_Solver()
{
	// Initializing all the data structures that will have to be used
	numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

void Sudoku_Solver::generate_permutations()
{
	do
	{
		permutations.push_back(numbers);
	} while (std::next_permutation(numbers.begin(), numbers.end()));
}


void Sudoku_Solver::solve_board()
{
	// read line by line
	for (int i = 0; i < board.BOARD_SIZE; ++i)
	{
		int correct_sequence[board.BOARD_SIZE];
		bool is_sequence_ok = true;

		for (int j = 0; j < board.BOARD_SIZE; ++j)
			// correct_sequence.push_back(board.get_number_at(i, j));
			correct_sequence[j] = board.get_number_at(i, j);

		// find a sequence of numbers for each line
		foo_rec(&graph.nodes, correct_sequence, i, 0, is_sequence_ok);

		// std::cout << "\ncorrect_sequence i = " << i << " ---> ";
		for (int j = 0; j < board.BOARD_SIZE; ++j)
		{
			board.set_number_at(correct_sequence[j], i, j);
			// std::cout << board.get_number_at(i, j) << ", ";
		}
		// std::cout << '\n';
	}
}


void Sudoku_Solver::foo_rec(const std::vector<Node> *current_nodes, int correct_sequence[], int i, int j, bool &is_sequence_ok)
{
	if (j == board.BOARD_SIZE) return;

	int current_number = board.get_number_at(i, j);

	if (current_number != 0)
	{ 
		// search the number in the graph
		auto it = std::find_if(current_nodes->begin(), current_nodes->end(), [current_number](const Node &node)
		{
			return node.value == current_number;
		});

		if (it == current_nodes->end())
		{
			// it means that a previous incorrect node was used, so it has to go back
			// and take the next node of that.

			std::cout << '\n' << "Element " << current_number << " not found." << '\n';
			is_sequence_ok = false;
			return;
		}

		int node_idx = std::distance(current_nodes->begin(), it);
		correct_sequence[j] = current_number;
		
		foo_rec((*current_nodes)[node_idx].next_nodes.get(), correct_sequence, i, j + 1, is_sequence_ok);
		
		if (!is_sequence_ok)
			correct_sequence[j] = 0;
		
		return;
	}

	long unsigned int nodes_idx = 0;
	long unsigned int end = (*current_nodes)[nodes_idx].next_nodes.get()->size();
	bool is_there_a_tmp_valid_node = false;
	
	for (; nodes_idx <= end && !is_there_a_tmp_valid_node; ++nodes_idx)
	{
		int number_taken_from_sequence = (*current_nodes)[nodes_idx].value; 

		if (!is_number_valid_in_x_line(number_taken_from_sequence, correct_sequence) ||
			!is_number_valid_in_y_line(number_taken_from_sequence, j) ||
			is_number_in_the_3x3_matrix(number_taken_from_sequence, i, j))
			continue;

		is_there_a_tmp_valid_node = true;
		correct_sequence[j] = number_taken_from_sequence;

		foo_rec((*current_nodes)[nodes_idx].next_nodes.get(), correct_sequence, i, j + 1, is_there_a_tmp_valid_node);

		if (!is_there_a_tmp_valid_node) is_sequence_ok = false;
		
		else is_sequence_ok = true;
	}

	if (!is_there_a_tmp_valid_node)
	{
		is_sequence_ok = false;
		correct_sequence[j] = 0;
		return;
	}
}

bool Sudoku_Solver::is_number_valid_in_x_line(int current_number, int current_sequence[])
{
	for (int i = 0; i < board.BOARD_SIZE; ++i)
		if (current_sequence[i] == current_number)
			return false;
	
	return true;
}

bool Sudoku_Solver::is_number_valid_in_y_line(int current_number, int x)
{
	for (int y = 0; y < board.BOARD_SIZE; ++y)
		if (board.get_number_at(y, x) == current_number)
			return false;

	return true;
}

bool Sudoku_Solver::is_number_in_the_3x3_matrix(int current_number, int i , int j)
{
	int y = (i / board.SUB_MATRIX_SIZE) * board.SUB_MATRIX_SIZE;
	const int start_of_x = (j / board.SUB_MATRIX_SIZE) * board.SUB_MATRIX_SIZE;
	const int end_of_y = y + board.SUB_MATRIX_SIZE;
	const int end_of_x = start_of_x + board.SUB_MATRIX_SIZE;

	for (; y < end_of_y; ++y)
		for (int x = start_of_x; x < end_of_x; ++x)
			if (board.get_number_at(y, x) == current_number)
				return true;

	return false;
}


// Solves the board
void Sudoku_Solver::run()
{
	generate_permutations();

	// Initialize graph
	graph.store_permutations(permutations);

	board.read_board_from_txt_file();
	board.print();

	solve_board();

	// ^^^ RESULT ^^^ 
	board.print();
}