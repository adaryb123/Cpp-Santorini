#include "Libraries.h"

#include "Engine.h"

void pick_move(const GameBoard game_board, const std::vector<Move> moves, Move& chosenMove){
    srand(time(0));
    int move_index = 0 + rand() % moves.size();
    chosenMove = moves[move_index];
}


bool ask_user_to_continue(){
    std::string user_input;
    std::cout << "Go next move? Y/N\n";
    std::getline( std::cin, user_input);
    return user_input == "Y" || user_input == "y";
}

int main()
{
    GameBoard game_board;
    std::vector<Move> black_moves, white_moves;
    Move selected_move;
    int end = 0;
    setup_board(game_board);
    std::cout << "Starting board:\n" << game_board;
    while(true){
        std::cout << "Black turn:\n";
        get_available_moves(game_board, 'b', black_moves);
        if (black_moves.size() == 0){
            std::cout << "black has no moves, white won!\n";
            break;
        }
        // std::cout << "Available black moves: \n";
        // for (size_t i = 0 ; i < black_moves.size() ; i++){
        //     std::cout << black_moves[i];
        // }
        pick_move(game_board,black_moves, selected_move);
        // std::cout << "chosen move: " << selected_move;

        update_board_after_move(game_board,selected_move,end);
        std::cout << "black picked move " << selected_move << '\n' << game_board << "\n";
        if (end == -1){
            std::cout << "black won!\n";
            break;
        }


        if (!ask_user_to_continue())
            break;
        std::cout << "White turn:\n";
        get_available_moves(game_board, 'w', white_moves);
        if (white_moves.size() == 0){
            std::cout << "white has no moves, black won!\n";
            break;
        }
        pick_move(game_board,white_moves, selected_move);
        update_board_after_move(game_board,selected_move,end);
        std::cout << "white picked move " << selected_move << '\n' << game_board << "\n";
        if (end == 1){
            std::cout << "white won!\n";
            break;
        }
        if (!ask_user_to_continue())
            break;
    }

	return 0;
}