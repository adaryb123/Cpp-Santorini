#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "GameBoard.h"

int main()
{
    printf("kek\n");

    GameBoard gb{};
    std::cout << gb << "\n";

    GameBoard testBoard{};
    testBoard.game_board[0][1].layer=3;
    testBoard.game_board[2][4].layer=2;
    testBoard.game_board[1][1].layer=1;
    testBoard.game_board[4][1].layer=3;
    testBoard.game_board[4][1].black_present = true;
    testBoard.game_board[3][3].white_present = true;
    testBoard.game_board[3][4].layer=3;
    testBoard.game_board[3][4].dome = true;

    std::cout << testBoard;

    Move testMove {2,2,3,3,2,3};
    std::cout << testMove;

	// std::vector<std::vector<char>> game_board;

	// setup_game(game_board);
	// print_game(game_board);
	
	return 0;
}