#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

int main() {
	Board *board_p = new Board();
	Game *game_p = new Game(board_p);

	Player *p1 = new Player();
	Player *p2 = new Player();


	game_p->start_play(p1, p2);


	return 0;
}