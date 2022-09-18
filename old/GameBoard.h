#pragma once

#include "Libraries.h"

#include "Tile.h"


void setup_players(std::vector<std::vector<Tile>>& game_board) {
    srand(time(0));
	for (int i = 0 ; i < 4; i++){
        while(true){
            int random_integer = 0 + rand() % 8;
            int row = random_integer / 3 + 1;
            int col = random_integer % 3 + 1;
            if (game_board[row][col].black_present == false && game_board[row][col].white_present == false){
                    if (i < 2){
                        game_board[row][col].black_present = true;
                    }
                    else{
                        game_board[row][col].white_present = true;
                    }
            break;
            }
        }
    }
}

class GameBoard final
{
public:                                                             
    GameBoard(){
        for (size_t i = 0; i < 5; i++)
        {
		game_board.push_back(std::vector<Tile>{});
		for (size_t j = 0; j < 5; j++)
			game_board[i].push_back(Tile{});
	    }

        setup_players(game_board);
    };

    std::vector<std::vector<Tile>> game_board;

    friend std::ostream& operator<<(std::ostream& lhs, const GameBoard& rhs);

};

std::ostream& operator<<(std::ostream& lhs, const GameBoard& rhs)
{
    lhs << "\n   |__A_______B_______C_______D_______E___\n";
    for (size_t i = 0; i < 5; i++){
        lhs << i+1 <<"  |";   
		for (size_t j = 0; j < 5; j++)
		{
            lhs << rhs.game_board[i][j] << " | ";       
        }
        lhs << "\n   |______|_______|_______|_______|_______|\n";
    }
    return lhs;
}
