#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

enum class Color { white, black };
enum class Enemy{ random, heuristic, minmax };
typedef struct Tile {
	int row;
	int col;
}tile;

/*user will set player color and type of enemy*/
void assign_start_variables(Color& player_color, Enemy& enemy, Color& enemy_color) {
	while (true) {
		bool error = false;
		std::string color_string, enemy_string;
		std::cout << "Welcome to Othello console game!\nChoose your color:\n";
		std::cout << "Press 1 for white (O)\nPress 2 for black (X)\n";
		std::cin >> color_string;
		if (color_string == "1") {
			player_color = Color::white;
			enemy_color = Color::black;
		}
		else if (color_string == "2") {
			player_color = Color::black;
			enemy_color = Color::white;
		}
		else {
			std::cout << "Invalid option. Try again!";
			error = true;
			continue;
		}

		std::cout << "\nChoose enemy AI to play against:\n";
		std::cout << "Press 1 for random enemy\nPress 2 for heuristic enemy\nPress 3 for minmax enemy\n";
		std::cin >> enemy_string;
		if (enemy_string == "1")
			enemy = Enemy::random;
		else if (enemy_string == "2")
			enemy = Enemy::heuristic;
		else if (enemy_string == "3")
			enemy = Enemy::minmax;
		else {
			std::cout << "Invalid option. Try again!\n\n";
			error = true;
			continue;
		}

		if (!error)
			break;
	}

	std::cout << "\nPlaying with ";
	if (player_color == Color::black)
		std::cout << "black";
	else if (player_color == Color::white)
		std::cout << "white";
	std::cout << " against ";
	if (enemy == Enemy::random)
		std::cout << "random";
	else if (enemy == Enemy::heuristic)
		std::cout << "heuristic";
	else if (enemy == Enemy::minmax)
		std::cout << "minmax";
	std::cout << " enemy.\n\n\n";
}

void setup_game(std::vector<std::vector<char>>& game_board) {
	for (size_t i = 0; i < 8; i++)
	{
		game_board.push_back(std::vector<char>{});
		for (size_t j = 0; j < 8; j++)
			game_board[i].push_back('-');
	}
	game_board[3][3] = 'O';
	game_board[4][4] = 'O';
	game_board[3][4] = 'X';
	game_board[4][3] = 'X';
}

void print_game(const std::vector<std::vector<char>>& game)
{
	std::cout << "\n    A B C D E F G H\n\n";
 	for (size_t i = 0; i < 8; i++)
	{
		std::cout << static_cast<int>(i+1) << "   ";
		for (size_t j = 0; j < 8; j++)
			std::cout << game[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

/* valid move format examples: 2A, 3h, 7d */
bool check_valid_input(const std::string input) {
	if (input.size() != 2)
		return false;

	char row, col;
	row = static_cast<char>(input[0]);
	if (row < '1' || row > '8')
		return false;

	col = static_cast<char>(input[1]);
	if (col < 'A' || col > 'H')
		return false;

	return true;
}

/* we use both string and structure representations for 1 tile of the game board*/
Tile string_to_tile(const std::string& input)					
{
	Tile output;
	char temp = input[0];
	output.row = temp - '1';
	output.col = static_cast<int>(input[1] - 'A');
	return output;
}

std::string tile_to_string(const Tile& input)			
{
	std::string output;
	output += std::to_string(input.row + 1);
	output += static_cast<char>(input.col + 'A');
	return output;
}

void print_possible_moves(const std::vector<tile> moves)
{
	std::cout<<"Possible moves are:\n";
	for (size_t i = 0; i < moves.size(); i++)
		std::cout << tile_to_string(moves[i]) << "\n";
}

/* Move is valid when the new placed tile and your existing tiles seals of 1 or more enemy tiles in horizontal, vertical, or diagonal lines*/
bool check_move_valid(std::vector<std::vector<char>> game, const Tile& tile, const Color& color)
{
	char enemy_piece, friendly_piece;

	if (color == Color::black) {
		game[tile.row][tile.col] = 'X';
		enemy_piece = 'O';
		friendly_piece = 'X';
	}
	else {
		game[tile.row][tile.col] = 'O';
		enemy_piece = 'X';
		friendly_piece = 'O';
	}

	//up
	if (tile.row - 1 >= 0 && game[tile.row - 1][tile.col] == enemy_piece) 
		for (int i = tile.row - 1; i >= 0; i--) {
			if (game[i][tile.col] == friendly_piece)
				return true;
			else if (game[i][tile.col] == '-')
				break;
		}
	

	//down
	if (tile.row + 1 <= 7 && game[tile.row + 1][tile.col] == enemy_piece) 
		for (int i = tile.row + 1; i <= 7; i++) {
			if (game[i][tile.col] == friendly_piece)
				return true;
			else if (game[i][tile.col] == '-')
				break;
		}
	

	//left
	if (tile.col - 1 >= 0 && game[tile.row][tile.col - 1] == enemy_piece) 
		for (int i = tile.col - 1; i >= 0; i--) {
			if (game[tile.row][i] == friendly_piece)
				return true;
			else if (game[tile.row][i] == '-')
				break;
		}

	//right
	if (tile.col + 1 <= 7 && game[tile.row][tile.col + 1] == enemy_piece) 
		for (int i = tile.col + 1; i <= 7; i++){
			if (game[tile.row][i] == friendly_piece)
				return true;
			else if (game[tile.row][i] == '-')
				break;
		}

	//up left
	if (tile.row - 1 >= 0 && tile.col -1 >= 0 && game[tile.row -1][tile.col -1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col - 1; i >= 0 && j >= 0; i--, j--) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	//up right
	if (tile.row - 1 >= 0 && tile.col + 1 <= 7 && game[tile.row - 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col + 1; i >= 0 && j <= 7; i--, j++) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	//down left
	if (tile.row + 1 <= 7 && tile.col - 1 >= 0 && game[tile.row + 1][tile.col - 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col - 1; i <= 7 && j >= 0; i++, j--) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	//down right
	if (tile.row + 1 <= 7 && tile.col + 1 <= 7 && game[tile.row + 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col + 1; i <= 7 && j <= 7; i++, j++) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	return false;
}

std::vector<Tile> find_possible_moves(const std::vector<std::vector<char>>& game, const Color& color)
{

	std::vector<Tile> valid_moves;

	for (int i = 0 ; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (game[i][j] != '-')
				continue;

			Tile current_move;
			current_move.row = i;
			current_move.col = j;
			if (check_move_valid(game, current_move, color))
			{
				valid_moves.push_back(current_move);
			}
		}
	return valid_moves;
}

/* add new placed tile and flip sealed enemy tiles*/
void update_game(std::vector<std::vector<char>>& game, const Tile& tile, const Color& color)
{
	char enemy_piece, friendly_piece;

	if (color == Color::black) {
		game[tile.row][tile.col] = 'X';
		enemy_piece = 'O';
		friendly_piece = 'X';
	}
	else {
		game[tile.row][tile.col] = 'O';
		enemy_piece = 'X';
		friendly_piece = 'O';
	}

	//up
	if (tile.row - 1 >= 0 && game[tile.row - 1][tile.col] == enemy_piece)
		for (int i = tile.row - 1; i >= 0; i--) {
			if (game[i][tile.col] == friendly_piece)
			{
				for (int j = i; j <= tile.row - 1; j++)
					game[j][tile.col] = friendly_piece;
				break;
			}
			else if (game[i][tile.col] == '-')
				break;

		}

	//down
	if (tile.row + 1 <= 7 && game[tile.row + 1][tile.col] == enemy_piece)
		for (int i = tile.row + 1; i <= 7; i++) {
			if (game[i][tile.col] == friendly_piece)
			{
				for (int j = i; j >= tile.row + 1; j--)
					game[j][tile.col] = friendly_piece;
				break;
			}
			else if (game[i][tile.col] == '-')
				break;
		}

	//left
	if (tile.col - 1 >= 0 && game[tile.row][tile.col - 1] == enemy_piece)
		for (int i = tile.col - 1; i >= 0; i--) {
			if (game[tile.row][i] == friendly_piece)
			{
				for (int j = i; j <= tile.col - 1; j++)
					game[tile.row][j] = friendly_piece;
				break;
			}
			else if (game[tile.row][i] == '-')
				break;
		}

	//right
	if (tile.col + 1 <= 7 && game[tile.row][tile.col + 1] == enemy_piece)
		for (int i = tile.col + 1; i <= 7; i++) {
			if (game[tile.row][i] == friendly_piece)
			{
				for (int j = i; j >= tile.col + 1; j--)
					game[tile.row][j] = friendly_piece;
				break;
			}
			else if (game[tile.row][i] == '-')
				break;
		}

	//up left
	if (tile.row - 1 >= 0 && tile.col - 1 >= 0 && game[tile.row - 1][tile.col - 1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col - 1; i >= 0 && j >= 0; i--, j--) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k <= tile.row - 1) && (l <= tile.col - 1); k++, l++)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}

	//up right
	if (tile.row - 1 >= 0 && tile.col + 1 <= 7 && game[tile.row - 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col + 1; i >= 0 && j <= 7; i--, j++) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k <= tile.row - 1) && (l >= tile.col + 1); k++, l--)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}
	

	//down left
	if (tile.row + 1 <= 7 && tile.col - 1 >= 0 && game[tile.row + 1][tile.col - 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col - 1; i <= 7 && j >= 0; i++, j--) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k >= tile.row + 1) && (l <= tile.col - 1); k--, l++)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}

	//down right
	if (tile.row + 1 <= 7 && tile.col + 1 <= 7 && game[tile.row + 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col + 1; i <= 7 && j <= 7; i++, j++) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k >= tile.row + 1) && (l >= tile.col + 1); k--, l--)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}

}

void player_turn(std::vector<std::vector<char>>& game,const std::vector<Tile>& possible_moves, const Color& color)
{
	std::string input;
	std::cout << "Your turn!\n";
	while (true)
	{
		std::cout << "Enter the row and column of the new piece: (example: 1A)\n";
		std::cin >> input;
		input[1] = static_cast<char>(toupper(input[1]));
		if (!check_valid_input(input))
		{
			std::cout << "Invalid input format. Try again.\n";
			continue;
		}
		Tile selected_move = string_to_tile(input);

		bool valid = false;
		for (auto move : possible_moves)
		{
			if (move.col == selected_move.col && move.row == selected_move.row) {
				valid = true;
				break;
			}
		}
		if (valid) {
			update_game(game, selected_move, color);
			break;
		}
		else
		{
			std::cout << "Invalid move. Try again.\n";
			print_possible_moves(possible_moves);
		}
	}
}

void print_ending_message(const std::vector<std::vector<char>>& game, const Color& player_color)
{
	int black_tiles = 0, white_tiles = 0;
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
		{
			if (game[i][j] == 'O')
				white_tiles++;
			else if (game[i][j] == 'X')
				black_tiles++;
		}

	std::cout << "Game ended!\n";
	std::cout << "Black tiles: " << black_tiles << "\n";
	std::cout << "White tiles: " << white_tiles << "\n";
	if (black_tiles == white_tiles) {
		std::cout << "Draw!\n";
	}
	else {
		Color winner = player_color;
		if (black_tiles > white_tiles)
			winner = Color::black;
		else if (white_tiles > black_tiles)
			winner = Color::white;

		if (winner == player_color)
			std::cout << "You won!\n";
		else
			std::cout << "You lost!\n";
	}
}

/* select random move from the available moves */
void enemy_turn_random(std::vector<std::vector<char>>& game, const std::vector<Tile>& possible_moves, const Color& color)
{
	std::cout << "Enemy turn!\n";
	print_possible_moves(possible_moves);
	srand(static_cast<int>(time(0)));
	int index = (rand() % (static_cast<int>(possible_moves.size())));
	Tile selected_move = possible_moves[index];
	std::cout << "Selected move " << tile_to_string(selected_move) << " with index " << index << "\n";
	update_game(game, selected_move, color);
}

/* normal tile is worth 1 point, edge tile is worth 2 and corner is worth 3 */
int get_tile_difference(const std::vector<std::vector<char>>& game, const Color& friendly)
{
	int black_tiles = 0, white_tiles = 0;
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 8; j++)
		{
			if (game[i][j] == 'O') 
			{
				if ((j == 0 || j == 7) && (i == 0 || i == 7))
					white_tiles += 3;
				else if (j == 0 || j == 7 || i == 0 || i == 7)
					white_tiles += 2;
				else
					white_tiles++;
			}
			else if (game[i][j] == 'X')
			{
				if ((j == 0 || j == 7) && (i == 0 || i == 7))
					black_tiles += 3;
				else if (j == 0 || j == 7 || i == 0 || i == 7)
					black_tiles += 2;
				else
					black_tiles++;
			}
		}

	if (friendly == Color::black)
		return black_tiles - white_tiles;
	else
		return white_tiles - black_tiles;
}

/* get heuristic value for each available move. We are counting tile difference minus number of available moves for enemy */
int calculate_heuristic(std::vector<std::vector<char>> game, const Tile& current_move, const Color& friendly_color)
{
	Color enemy_color;
	if (friendly_color == Color::black)
		enemy_color = Color::white;
	else
		enemy_color = Color::black;

	update_game(game, current_move, friendly_color);
	return get_tile_difference(game, friendly_color) - static_cast<int>(find_possible_moves(game, enemy_color).size());
}

/* select the move with best heuristic value */
void enemy_turn_heuristic(std::vector<std::vector<char>>& game, const std::vector<Tile>& possible_moves, const Color& color)
{
	int max = calculate_heuristic(game, possible_moves[0], color);
	Tile best_move = possible_moves[0];
	for (auto move : possible_moves)
	{
		int heuristic_val = calculate_heuristic(game, move, color);
		//std::cout << "Move " << tile_to_string(move) << " heuristic value " << heuristic_val << '\n';
		if (heuristic_val > max) {
			max = heuristic_val;
			best_move = move;
		}
	}
	//std::cout << " Best move is " << tile_to_string(best_move) << " with heuristic value " << max << '\n';
	update_game(game, best_move, color);
}

int main()
{
	Color player_color, enemy_color;
	Enemy enemy;
	assign_start_variables(player_color, enemy,enemy_color);
	std::vector<std::vector<char>> game_board;
	setup_game(game_board);
	print_game(game_board);
	
	while(true)
	{
		Color on_turn;
		bool black_skip = false;
		bool white_skip = false;

		/* black's turn */
		on_turn = Color::black;
		std::vector<Tile> possible_moves_black = find_possible_moves(game_board, on_turn);
		if (possible_moves_black.empty())
		{
			std::cout << "No available moves for black player.\n";
			black_skip = true;
		}
		else {
			if (player_color == Color::black)
				player_turn(game_board,possible_moves_black,player_color);
			else
			{
				if (enemy == Enemy::random)
					enemy_turn_random(game_board, possible_moves_black, enemy_color);
				else if (enemy == Enemy::heuristic)
					enemy_turn_heuristic(game_board, possible_moves_black, enemy_color);
			}
		}
		print_game(game_board);

		/* white's turn */
		on_turn = Color::white;
		std::vector<Tile> possible_moves_white = find_possible_moves(game_board, on_turn);
		if (possible_moves_white.empty())
		{
			std::cout << "No available moves for white player.\n";
			white_skip = true;
		}
		else {
			if (player_color == Color::white)
				player_turn(game_board,possible_moves_white,player_color);
			else
			{
				if (enemy == Enemy::random)
					enemy_turn_random(game_board, possible_moves_white, enemy_color);
				else if (enemy == Enemy::heuristic)
					enemy_turn_heuristic(game_board, possible_moves_white, enemy_color);
			}
		}
		print_game(game_board);

		if (black_skip && white_skip)
			break;
	}
	print_ending_message(game_board, player_color);
	return 0;
}
