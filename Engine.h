#pragma once

#include "Libraries.h"

typedef struct Tile {
    int level;
    bool dome;
    bool white_present;
    bool black_present;
} Tile;

typedef std::vector<std::vector<Tile>> GameBoard;

typedef struct Move {
    int row_from;
    int col_from;
    int row_to;
    int col_to;
    int row_build;
    int col_build;
} Move;

typedef struct PlayerPosition{
    int row;
    int col;
    int level;
} PlayerPosition;

std::ostream& operator<<(std::ostream& lhs, const Tile& rhs)
{
    int spaces = 4;
    if(rhs.level == 0){
        spaces = 4;
    }
    else if (rhs.level == 1){
        lhs << "C";
        spaces = 3;
    }
    else if (rhs.level == 2){
        lhs << "CC";
        spaces = 2;
    }
    else if (rhs.level == 3){
        lhs << "CCC";
        spaces = 1;
    }
    
    if (rhs.dome){
        lhs << "D";
    }
    else if (rhs.white_present){
        lhs << "_O";
        spaces--;
    }
    else if (rhs.black_present){
        lhs << "_X";
        spaces--;
    }
    else{
        spaces++;
    }

    for (int i = 0 ; i < spaces; i++)
        lhs << " ";

    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const GameBoard& rhs)
{
    lhs << "\n   |__A_______B_______C_______D_______E___\n";
    for (size_t i = 0; i < 5; i++){
        lhs << i+1 <<"  |";   
		for (size_t j = 0; j < 5; j++)
		{
            lhs << rhs[i][j] << " | ";       
        }
        lhs << "\n   |______|_______|_______|_______|_______|\n";
    }
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const Move& rhs)
{
    lhs << "MOVE [" << rhs.row_from+1 << "][" << static_cast<char>('A' + rhs.col_from) << "]->[" << rhs.row_to+1 << "][" << static_cast<char>('A' + rhs.col_to)
        << "] build: [" << rhs.row_build+1 << "][" << static_cast<char>('A' + rhs.col_build) <<"]\n";

    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const PlayerPosition& rhs)
{
    lhs << rhs.row << rhs.col << " level " << rhs.level << "\n";
    return lhs;
}

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

void setup_board(std::vector<std::vector<Tile>>& game_board){
    for (size_t i = 0; i < 5; i++){
		game_board.push_back(std::vector<Tile>{});
		for (size_t j = 0; j < 5; j++){
			game_board[i].push_back(Tile{});
            game_board[i][j].level = 0;
            game_board[i][j].dome = false;
            game_board[i][j].white_present = false;
            game_board[i][j].black_present = false;
        }
	}
    setup_players(game_board);
}


void get_player_positions(PlayerPosition& black1, PlayerPosition& black2, PlayerPosition& white1, PlayerPosition& white2, const GameBoard game_board)
{
    bool first_black = true;
    bool first_white = true;
    for (size_t i = 0; i < 5; i++){
        for (size_t j = 0; j < 5; j++){
            if (game_board[i][j].black_present){
                if (first_black){
                    first_black = false;
                    black1.row = i;
                    black1.col = j;
                    black1.level = game_board[i][j].level;
                }
                else{
                    black2.row = i;
                    black2.col = j;
                    black2.level = game_board[i][j].level;
                }
            }
            else if (game_board[i][j].white_present){
                if (first_white){
                    first_white = false;
                    white1.row = i;
                    white1.col = j;
                    white1.level = game_board[i][j].level;
                }
                else{
                    white2.row = i;
                    white2.col = j;
                    white2.level = game_board[i][j].level;
                }
            }
        }
    }
}

bool is_valid_build(const int row, const int col, const GameBoard game_board){
    if (row < 0 || row > 4 || col < 0 || col > 4){
        return false;
    }
    else if (game_board[row][col].black_present || game_board[row][col].white_present || game_board[row][col].dome){
        return false;
    }
    else{
        return true;
    }
}

void get_possible_builds(const int row, const int col, const GameBoard game_board, std::vector<std::tuple<int,int>>& builds){
    builds.clear();
    
    if (is_valid_build(row-1,col-1,game_board))
        builds.push_back({row-1,col-1});
    
    if (is_valid_build(row-1,col,game_board))
        builds.push_back({row-1,col});

    if (is_valid_build(row-1,col+1,game_board))
        builds.push_back({row-1,col+1});

    if (is_valid_build(row+1,col-1,game_board))
        builds.push_back({row+1,col-1});

    if (is_valid_build(row+1,col,game_board))
        builds.push_back({row+1,col});

    if (is_valid_build(row+1,col+1,game_board))
        builds.push_back({row+1,col+1});

    if (is_valid_build(row,col-1,game_board))
        builds.push_back({row,col-1});

    if (is_valid_build(row,col+1,game_board))
        builds.push_back({row,col+1});
    
}
        

bool is_valid_move(const int row, const int col, const int current_level, const GameBoard game_board){
    if (row < 0 || row > 4 || col < 0 || col > 4){
        return false;
    }
    else if (game_board[row][col].black_present || game_board[row][col].white_present || game_board[row][col].dome){
        return false;
    }
    else if (game_board[row][col].level > (current_level + 1)){
        return false;
    }
    else{
        return true;
    }
}

void get_possible_moves_for_worker(const PlayerPosition player, const GameBoard game_board, std::vector<Move>& moves){
    int row = player.row;
    int col = player.col;
    int level = player.level;

    std::vector<std::tuple<int,int>> builds;

    // move up left
    if (is_valid_move(row-1,col-1,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row-1,col-1,row,col});   

        get_possible_builds(row-1,col-1,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row-1,col-1,x,y});
        }
    }

    // move up
    if (is_valid_move(row-1,col,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row-1,col,row,col});   

        get_possible_builds(row-1,col,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row-1,col,x,y});
        }
    }

    // move up right
    if (is_valid_move(row-1,col+1,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row-1,col+1,row,col});   

        get_possible_builds(row-1,col+1,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row-1,col+1,x,y});
        }
    }
    
    // move down left
    if (is_valid_move(row+1,col-1,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row+1,col-1,row,col});   

        get_possible_builds(row+1,col-1,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row+1,col-1,x,y});
        }
    }

    // move down
    if (is_valid_move(row+1,col,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row+1,col,row,col});   

        get_possible_builds(row+1,col,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row+1,col,x,y});
        }
    }

    // move down right
    if (is_valid_move(row+1,col+1,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row+1,col+1,row,col});   

        get_possible_builds(row+1,col+1,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row+1,col+1,x,y});
        }
    }

    // move left
    if (is_valid_move(row,col-1,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row,col-1,row,col});   

        get_possible_builds(row,col-1,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row,col-1,x,y});
        }
    }

    // move right
    if (is_valid_move(row,col+1,level,game_board)){
        // you can always build on the tile where you stood before
        moves.push_back(Move{row,col,row,col+1,row,col});   

        get_possible_builds(row,col+1,game_board,builds);
        for (auto&& tuple: builds)
        {
            int x,y;
            std::tie(x,y) = tuple;
            moves.push_back(Move{row,col,row,col+1,x,y});
        }
    }
}

void get_available_moves(const GameBoard game_board, const char player, std::vector<Move>& moves){
    PlayerPosition black1,black2,white1,white2;
    get_player_positions(black1,black2,white1,white2,game_board);
    std::vector<Move> black1_moves, black2_moves, white1_moves, white2_moves;
    
    get_possible_moves_for_worker(black1, game_board, black1_moves);
    get_possible_moves_for_worker(black2, game_board, black2_moves);
    get_possible_moves_for_worker(white1, game_board, white1_moves);
    get_possible_moves_for_worker(white2, game_board, white2_moves);

    if (player == 'b'){
        black1_moves.insert(black1_moves.end(), black2_moves.begin(), black2_moves.end());
        moves = black1_moves;
    }
    else if (player == 'w'){
        white1_moves.insert(white1_moves.end(), white2_moves.begin(), white2_moves.end());
        moves = white1_moves;
    }

}


void update_board_after_move(GameBoard& game_board, const Move move, int& winner){
    GameBoard actual_board = game_board;
    if (actual_board[move.row_from][move.col_from].black_present){
        actual_board[move.row_from][move.col_from].black_present = false;
        actual_board[move.row_to][move.col_to].black_present = true;

        if (actual_board[move.row_to][move.col_to].level == 3)
            winner = -1;
    }
    else if (actual_board[move.row_from][move.col_from].white_present){
        actual_board[move.row_from][move.col_from].white_present = false;
        actual_board[move.row_to][move.col_to].white_present = true;

        if (actual_board[move.row_to][move.col_to].level == 3)
            winner = 1;
    }

    if (actual_board[move.row_build][move.col_build].level == 3)
        actual_board[move.row_build][move.col_build].dome = true;
    else
        actual_board[move.row_build][move.col_build].level++;

    game_board = actual_board;
}