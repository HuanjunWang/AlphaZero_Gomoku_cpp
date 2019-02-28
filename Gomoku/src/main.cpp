#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

int main() {
	Board *board_p = new Board(6,4);
	Game *game_p = new Game(board_p);

	Player *p1 = new RandPlayer("Tom");
	Player *p2 = new HumanPlayer("Pang");


	game_p->start_play(p1, p2, true);

	getchar();
	return 0;
}