#pragma once

#include "Libraries.h"

#include "Engine.h"

int evaluate(const GameBoard board){
    PlayerPosition w1,w2,b1,b2;
    int heuristic_value = 0;
    get_player_positions(b1,b2,w1,w2,board);
    heuristic_value = 2*b1.level + 2*b2.level - w1.level - w2.level;
    if (b1.level == 3 || b2.level == 3)
        heuristic_value = 100;
    else if (w1.level == 3 || w2.level == 3)
        heuristic_value = -100;

    return heuristic_value;
}

std::tuple<int,Move> mini( int depth , const GameBoard current_board, const std::vector<Move> available_moves, const char current_player);

std::tuple<int,Move> maxi( int depth , const GameBoard current_board, const std::vector<Move> available_moves, const char current_player) {
    int max = -99999;
    Move bestMove = available_moves[0];
    char next_player;
    if (current_player == 'b')
        next_player = 'w';
    else if (current_player == 'w')
        next_player = 'b';

    for (size_t i = 0 ; i < available_moves.size() ; i++) {
        int score, winner = 0;
        GameBoard new_board = current_board;
        update_board_after_move(new_board, available_moves[i],winner);
        if (winner != 0){
            return {99999, available_moves[i]};
        }

        if (depth == 0){
            score = evaluate(new_board);
        }
        else{
            std::vector<Move> new_moves;
            Move garbage;
            get_available_moves(new_board,next_player,new_moves);
            std::tie(score,garbage) = mini( depth - 1, new_board, new_moves, next_player);
        }

        if( score > max ){
            max = score;
            bestMove = available_moves[i];
        }
    }
    return {max,bestMove};
}

std::tuple<int,Move> mini( int depth , const GameBoard current_board, const std::vector<Move> available_moves, const char current_player){
    int min = 99999;
    Move bestMove = available_moves[0];
    char next_player;
    if (current_player == 'b')
        next_player = 'w';
    else if (current_player == 'w')
        next_player = 'b';

    for (size_t i = 0 ; i < available_moves.size() ; i++) {
        int score, winner = 0;
        GameBoard new_board = current_board;
        update_board_after_move(new_board, available_moves[i],winner);
        if (winner != 0){
            return {99999, available_moves[i]};
        }

        if (depth == 0){
            score = -evaluate(new_board);
        }
        else{
            std::vector<Move> new_moves;
            Move garbage;
            get_available_moves(new_board,next_player,new_moves);
            std::tie(score,garbage) = maxi( depth - 1, new_board, new_moves, next_player);
        }

        if( score < min ){
            min = score;
            bestMove = available_moves[i];
        }
    }
    return {min,bestMove};
}


/*
std::tuple<int,Move> mini( int depth ) {
    // if ( depth == 0 ) return -evaluate();
    int min = 99999;
    for ( all moves) {
        score = maxi( depth - 1 );
        if( score < min )
            min = score;
    }
    return min;
}*/