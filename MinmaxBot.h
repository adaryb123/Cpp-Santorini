#pragma once

#include "Libraries.h"

#include "GameBoard.h"

#include "Move.h"

#include "GameEngine.h"

// heuristic function
int evaluate(GameBoard current_board, const char current_player){
    playerPosition w1,w2,b1,b2;
    int heuristic_value = 0;
    get_player_positions(b1,b2,w1,w2,current_board.game_board);
    if (current_player == 'b'){
        heuristic_value = b1.level + b2.level - w1.level - w2.level;
        if (b1.level == 3 || b2.level == 3)
            heuristic_value = 100;
        else if (w1.level == 3 || w2.level == 3)
            heuristic_value = -100;
    }
    else if (current_player == 'w'){
        heuristic_value = w1.level + w2.level - b1.level - b2.level;
        if (w1.level == 3 || w2.level == 3)
            heuristic_value = 100;
        else if (b1.level == 3 || b2.level == 3)
            heuristic_value = -100;
    }
    return heuristic_value;
}

int mini( int depth, const std::vector<Move>  generated_moves, GameBoard generated_board, const char active_player);

int maxi(  int depth, const std::vector<Move>  generated_moves, GameBoard generated_board, const char active_player) {
    if ( depth == 0 ) return evaluate(generated_board,active_player);
    int max = -99999;
    char next_player;
    if (active_player == 'b')
        next_player = 'w';
    else if (active_player == 'w')
        next_player = 'b';

    for (size_t i = 0 ; i < generated_moves.size(); i++) {
        int score = 0;
        Move currentMove = generated_moves[i];
        GameBoard newBoard = generated_board;
        int winner = 0;
        std::vector<Move> new_moves;
        update_board_after_move(newBoard, currentMove,winner);
        get_available_moves(newBoard.game_board, next_player, new_moves);
        score = mini( depth - 1 , new_moves, newBoard, next_player);
        if( score > max )
            max = score;
    }
    return max;
}

int mini( int depth, const std::vector<Move>  generated_moves, GameBoard generated_board, const char active_player) {
    if ( depth == 0 ) return -evaluate(generated_board,active_player);
    int min = 99999;
    char next_player;
    if (active_player == 'b')
        next_player = 'w';
    else if (active_player == 'w')
        next_player = 'b';

    for (size_t i = 0 ; i < generated_moves.size() ; i++) {
        int score = 0;
        Move currentMove = generated_moves[i];
        GameBoard newBoard = generated_board;
        int winner = 0;
        std::vector<Move> new_moves;
        update_board_after_move(newBoard, currentMove,winner);          //winnera zakomponovat
        get_available_moves(newBoard.game_board, next_player, new_moves);
        score = maxi( depth - 1 , new_moves, generated_board, next_player);
        if( score < min )
            min = score;
    }
    return min;
}

void pick_move(const GameBoard game_board, const std::vector<Move> moves, Move& chosenMove, const char active_player){
    int score , maxscore = -9999;
    for (size_t i = 0 ; i < moves.size(); i++){
        score = maxi(3,moves, game_board, active_player);
        if (score > maxscore){
            maxscore = score;
            chosenMove = moves[i];
        }
        break;
    }
}