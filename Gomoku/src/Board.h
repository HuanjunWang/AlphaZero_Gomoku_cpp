#pragma once

#include <assert.h>
#include <vector>
#include <unordered_map>

typedef enum {
	NONE,
	PLAYER1,
	PLAYER2,
	BOTH
} PLAYER;

class Location {
public:
	int h;
	int w;

	Location() :h(-1), w(-1) {}
	Location(int h, int w) :h(h), w(w) {}
};

class Board {
private:
	int board_width;
	int board_size;
	int n_in_row;

	PLAYER current_player;
	int steps;
	int last_move;
	std::vector<int> availables;
	std::unordered_map<int, PLAYER> states;

public:
	Board() :board_width(8), board_size(64), n_in_row(5) {}

	Board(int board_width, int n_in_row) :board_width(board_width), board_size(board_width * board_width), n_in_row(n_in_row) {
		assert(board_width > n_in_row);
	}

	void init_board(PLAYER start_player);

	Location move_to_location(int move);

	int location_to_move(Location& location);


	// TODO
	//void current_state();

	void do_move(int move);

	PLAYER get_winner();

	PLAYER get_current_player();

	int get_width() { return board_width; }

	int get_state(int move) { return states.at(move); }

	std::vector<int> * get_availables(){return & availables;}

	bool is_valid_move(int move);
	bool is_valid_move(int h, int w);

};