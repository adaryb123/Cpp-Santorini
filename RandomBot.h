#pragma once

#include "Libraries.h"

#include "GameBoard.h"

#include "Move.h"

void pick_move(const GameBoard game_board, const std::vector<Move> moves, Move& chosenMove){
    srand(time(0));
    int move_index = 0 + rand() % moves.size();
    chosenMove = moves[move_index];
}