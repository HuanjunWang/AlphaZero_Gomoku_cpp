#include <algorithm>
#include <iostream>
#include "Player.h"



int RandPlayer::get_action(Board * board_p)
{
	auto availables = board_p->get_availables();
	auto i = rand() % availables->size();

	auto move = availables->at(i);
	std::cout << name << " take action:" << move << std::endl;;
	return move;
}


int HumanPlayer::get_action(Board * board_p)
{
	int w, h;

	std::cout << "Your action:";
	std::cin >> h >> w;
	auto move = board_p->location_to_move(Location(h, w));

	while (true) {
		if (board_p->is_valid_move(h, w))
		{
			std::cout << name << " take action:" << move << std::endl;;
			return move;
		}
			
		std::cout << "Invalid action, please enter again:";
		std::cin >> h >> w;
		move = board_p->location_to_move(Location(h, w));
	}

}
