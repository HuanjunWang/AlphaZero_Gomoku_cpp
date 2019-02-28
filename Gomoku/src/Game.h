#pragma once

#include "Board.h"
#include "Player.h"

class Game {
	Board * board_p;

public:
	Game(Board* board_p) :board_p(board_p) {}

	void show(Player* p1_p, Player * p2_p);

	void start_play(Player* p1_p, Player* p2_p, bool is_shown);
};