#include "board.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

Board::Board()
{
	matrix.resize(BOARD_SIZE, std::vector<int>(BOARD_SIZE));
}

int Board::get_number_at(int y, int x)
{
	if (y < 0 || y >= BOARD_SIZE ||
		x < 0 || x >= BOARD_SIZE)
		throw std::out_of_range("\nIndex out of range.\n");

	return matrix[y][x];
}

void Board::set_number_at(int number, int y, int x)
{
	if (y < 0 || y >= BOARD_SIZE ||
		x < 0 || x >= BOARD_SIZE)
		throw std::out_of_range("\nIndex out of range.\n");
		
	matrix[y][x] = number;
}


void Board::read_board_from_txt_file()
{
	std::ifstream in_file(IN_FILE);
	// std::ifstream in_file("../data/input.txt");

	if (!in_file)	
	{
		std::cout << "\nError occured while opening " << IN_FILE << ".\n";
		in_file.close();
		return;
	}

	std::string line;
	int i = 0, j = 0;

	while (std::getline(in_file, line))
	{
		std::stringstream ss(line);
		int value;

		while (ss >> value)
		{
			matrix[i][j] = value;
			j++;
		}

		i++;
		j = 0;
	}
	
	in_file.close();
}


void Board::print()
{
	std::cout << "\nSTART\n";
	for (const std::vector<int> &row : matrix)
	{
		for (const int &element : row)
			std::cout << element << ' ';

		std::cout << '\n';
	}
	std::cout << "\nEND\n";
}