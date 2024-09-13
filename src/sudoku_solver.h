#pragma once

#include "board.h"
#include "graph.h"
#include <vector>

class Sudoku_Solver
{
public:
	Sudoku_Solver();
	~Sudoku_Solver() = default;

	void run();


private:
	void generate_permutations();
	void solve_board();

	void foo_rec(const std::vector<Node> *current_nodes, int correct_sequence[], int i, int j, bool &is_sequence_ok);

	bool is_number_valid_in_x_line(int current_number, int current_sequence[]);
	bool is_number_valid_in_y_line(int current_number, int j);
	bool is_number_in_the_3x3_matrix(int current_number, int i , int j);


	static const int N_OF_NUMBERS = 9;

	std::vector<int> numbers;
	std::vector<std::vector<int>> permutations;

	Graph graph;
	Board board;
};