#include "Board.h"



void Board::init_board(PLAYER start_player) {
	this->current_player = start_player;
	last_move = -1;
	steps = 0;

	for (auto i = 0; i < board_size; i++) {
		this->availables.push_back(i);
		this->states[i] = PLAYER::NONE;
	}
}

Location Board::move_to_location(int move)
{
	auto h = move / board_width;
	auto w = move % board_width;
	return Location(h, w);
}

int Board::location_to_move(Location& location)
{
	return location.h * board_width + location.w;
}

void Board::do_move(int move)
{
	states[move] = current_player;

	// TODO Bug here
	for (auto it = availables.begin(); it != availables.end();) {
		if (*it == move) {
			availables.erase(it);
			break;
		}
	}
	current_player = current_player == PLAYER2 ? PLAYER1: PLAYER2;
}

PLAYER Board::get_winner()
{
	// No enough steps to win
	if ((steps + 1) / board_width < 2)
		return PLAYER::NONE;

	for (auto it = states.begin(); it != states.end(); ++it) {
		auto player = it->second;
		if (player == PLAYER::NONE)
			continue;
		
		auto move = it->first;
		auto h = move / board_width;
		auto w = move % board_width;
	
		// Check the four derections possible to win
		if (w <= board_width - n_in_row) {	
			auto j = 1;
			for (; j < n_in_row; j++) {
				if (states[move + j] != player) break;
			}	
			if (j == n_in_row)
				return player;
		}

		if (h <= board_width - n_in_row) {
			auto j = 1;
			for (; j < n_in_row; j++) {
				if (states[move + j*board_width] != player) break;
			}
			if (j == n_in_row)
				return player;
		}

		if (h <= board_width - n_in_row && w <= board_width - n_in_row) {
			auto j = 1;
			for (; j < n_in_row; j++) {
				if (states[move + j*board_width + j] != player) break;
			}
			if (j == n_in_row)
				return player;
		}

		if (h <= board_width - n_in_row && w >= board_width-1) {
			auto j = 1;
			for (; j < n_in_row; j++) {
				if (states[move + j*board_width - j] != player) break;
			}
			if (j == n_in_row)
				return player;
		}
	}

	return PLAYER::NONE;
}

PLAYER Board::get_current_player()
{
	return current_player;
}
