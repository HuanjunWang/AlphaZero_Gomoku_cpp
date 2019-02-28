#include "Game.h"
#include <iostream>
#include <stdio.h>

void Game::show(Player * p1_p, Player * p2_p)
{
	auto width = board_p->get_width();
	std::cout << "Player:" << p1_p->name << " With X" << std::endl;
	std::cout << "Player:" << p2_p->name << " With O" << std::endl << std::endl;

	for (auto x = 0; x < width; x++) {
		printf("%4d", x);
	}
	printf("\r\n");
	for (auto i = 0; i < width; i++) {
		printf("\n");
		printf("%d", i);
		for (auto j = 0; j < width; j++) {
			auto loc = i * width + j;
			auto p = board_p->get_state(loc);

			if (p == PLAYER::PLAYER1) {
				printf("  X ");
			}
			else if (p == PLAYER::PLAYER2) {
				printf("  O ");
			}
			else
				printf("  - ");
		}
		printf("\n");
	}

}

void Game::start_play(Player * p1_p, Player * p2_p, bool is_shown)
{
	p1_p->player = PLAYER::PLAYER1;
	p2_p->player = PLAYER::PLAYER2;
	board_p->init_board(PLAYER::PLAYER1);

	if (is_shown) 
		show(p1_p, p2_p);

	while (true) {
		auto player_p = board_p->get_current_player() == PLAYER::PLAYER1 ? p1_p : p2_p;
		auto action = player_p->get_action(board_p);
		board_p->do_move(action);

		if (is_shown)
			show(p1_p, p2_p);

		auto winner = board_p->get_winner();

		if (winner == PLAYER::NONE) 
			continue;
			
		if (winner == PLAYER::PLAYER1) {
			std::cout << p1_p->name << " Win!!!" << std::endl;
		}
		else if (winner == PLAYER::PLAYER2) {
			std::cout << p2_p->name << " Win!!!" << std::endl;
		}
		else if (winner == PLAYER::BOTH) {
			std::cout << "Draw Game!!!" << std::endl;
		}
		getchar();
		break;
	}


}




