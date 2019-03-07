#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#include "MCTSPlayer.h"


std::unordered_map<int, float> random_policy(Board* board_p) {
	auto availables = board_p->get_availables();
	std::unordered_map<int, float> res;
	for (auto it = availables->begin(); it != availables->end(); ++it) {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		res.insert({ *it, r });
	}

	return res;
}

std::unordered_map<int, float> normal_policy(Board* board_p) {
	auto availables = board_p->get_availables();
	std::unordered_map<int, float> res;
	for (auto it = availables->begin(); it != availables->end(); ++it) {
		float r = static_cast<float> (1.0 / availables->size());
		res.insert({ *it, r });
	}

	return res;
}



int main() {
	Board *board_p = new Board(6,4);
	Game *game_p = new Game(board_p);

	//Player *p1 = new RandPlayer("Tom");
	Player *p1 = new HumanPlayer("Pang");
	Player *p2 = new MCTSPlayer("MCTS", 2000, 5.0, random_policy, normal_policy);

	game_p->start_play(p2, p1, true);


	delete board_p;
	delete game_p;
	delete p1;
	delete p2;

	getchar();
	return 0;
}