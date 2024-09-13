#pragma once

#include <vector>

#define IN_FILE "data/input.txt"
#define OUT_FILE "data/output.txt"

class Board
{
public:
	Board();
	int get_number_at(int y, int x);
	void set_number_at(int number, int y, int x);

	void read_board_from_txt_file();
	void print();

	static const int BOARD_SIZE = 9;
	static const int SUB_MATRIX_SIZE = 3;

private:
	std::vector<std::vector<int>> matrix;
};