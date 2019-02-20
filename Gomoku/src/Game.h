#pragma once

#include "Board.h"
#include "Player.h"

class Game {
	Board * board;

public:
	Game(Board* board) :board(board) {}
	void show();
	void start_play(Player* p1, Player* p2, bool is_shown);
};