#pragma once

#include "Board.h"

#include <string>

class Player {

public:
	std::string  name;
	PLAYER player;
public:
	Player(std::string name) :name(name) {}
	virtual int get_action(Board* board_p)=0;
};


class RandPlayer : public Player {
public: 
	RandPlayer(std::string name) : Player(name) {}
	int get_action(Board* board_p);
};

class HumanPlayer :public Player {
public:
	HumanPlayer(std::string name) :Player(name) {}
	int get_action(Board* board_p);
};