#pragma once

#include "Libraries.h"

#include "Tile.h"
#include "GameBoard.h"
#include "Move.h"


struct playerPosition{
    int row;
    int col;
    int level;
};

void get_player_positions(playerPosition& black1, playerPosition& black2, playerPosition& white1, playerPosition& white2, const std::vector<std::vector<Tile>> game_board)
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
                    black1.level = game_board[i][j].layer;
                }
                else{
                    black2.row = i;
                    black2.col = j;
                    black2.level = game_board[i][j].layer;
                }
            }
            else if (game_board[i][j].white_present){
                if (first_white){
                    first_white = false;
                    white1.row = i;
                    white1.col = j;
                    white1.level = game_board[i][j].layer;
                }
                else{
                    white2.row = i;
                    white2.col = j;
                    white2.level = game_board[i][j].layer;
                }
            }
        }
    }
}

bool is_valid_build(const int row, const int col, const std::vector<std::vector<Tile>> game_board){
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

void get_possible_builds(const int row, const int col, const std::vector<std::vector<Tile>> game_board, std::vector<std::tuple<int,int>>& builds){
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
        

bool is_valid_move(const int row, const int col, const int current_level, const std::vector<std::vector<Tile>> game_board){
    if (row < 0 || row > 4 || col < 0 || col > 4){
        return false;
    }
    else if (game_board[row][col].black_present || game_board[row][col].white_present || game_board[row][col].dome){
        return false;
    }
    else if (game_board[row][col].layer > (current_level + 1)){
        return false;
    }
    else{
        return true;
    }
}

void get_possible_moves_for_worker(const playerPosition player, const std::vector<std::vector<Tile>> game_board, std::vector<Move>& moves){
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

void get_available_moves(const std::vector<std::vector<Tile>> game_board, const char player, std::vector<Move>& moves){
    playerPosition black1,black2,white1,white2;
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
    std::vector<std::vector<Tile>>  actual_board = game_board.game_board;
    if (actual_board[move.row_from][move.col_from].black_present){
        actual_board[move.row_from][move.col_from].black_present = false;
        actual_board[move.row_to][move.col_to].black_present = true;

        if (actual_board[move.row_to][move.col_to].layer == 3)
            winner = -1;
    }
    else if (actual_board[move.row_from][move.col_from].white_present){
        actual_board[move.row_from][move.col_from].white_present = false;
        actual_board[move.row_to][move.col_to].white_present = true;

        if (actual_board[move.row_to][move.col_to].layer == 3)
            winner = 1;
    }

    if (actual_board[move.row_build][move.col_build].layer == 3)
        actual_board[move.row_build][move.col_build].dome = true;
    else
        actual_board[move.row_build][move.col_build].layer++;

    game_board.game_board = actual_board;

}