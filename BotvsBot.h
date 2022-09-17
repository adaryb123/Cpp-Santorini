#pragma once

#include "Libraries.h"

#include "GameEngine.h"

#include "MinmaxBot.h"

bool ask_user_to_continue(){
    std::string user_input;
    std::cout << "Go next move? Y/N\n";
    std::getline( std::cin, user_input);
    return user_input == "Y" || user_input == "y";
}

void main_loop(){
    GameBoard board;
    std::vector<Move> black_moves, white_moves;
    Move selected_move;
    int end = 0;
    std::cout << "Starting board:\n" << board;
    while(true){
        std::cout << "Black turn:\n";
        get_available_moves(board.game_board, 'b', black_moves);
        if (black_moves.size() == 0){
            std::cout << "black has no moves, white won!\n";
            break;
        }
        // std::cout << "Available black moves: \n";
        // for (size_t i = 0 ; i < black_moves.size() ; i++){
        //     std::cout << black_moves[i];
        // }
        pick_move(board,black_moves, selected_move,'b');
        std::cout << "chosen move: " << selected_move;

        update_board_after_move(board,selected_move,end);
        std::cout << "black picked move " << selected_move << '\n' << board << "\n";
        if (end == -1){
            std::cout << "black won!\n";
            break;
        }


        if (!ask_user_to_continue())
            break;
        std::cout << "White turn:\n";
        get_available_moves(board.game_board, 'w', white_moves);
        if (white_moves.size() == 0){
            std::cout << "white has no moves, black won!\n";
            break;
        }
        pick_move(board,white_moves, selected_move,'w');
        update_board_after_move(board,selected_move,end);
        std::cout << "white picked move " << selected_move << '\n' << board << "\n";
        if (end == 1){
            std::cout << "white won!\n";
            break;
        }
        if (!ask_user_to_continue())
            break;
    }
}