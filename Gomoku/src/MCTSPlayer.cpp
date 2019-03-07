#include <math.h>
#include "MCTSPlayer.h"
#include <time.h>
#include <iostream>

bool TreeNode::is_root()
{
	return parent_p == NULL;
}

bool TreeNode::is_leaf()
{
	return children.empty();
}


// new children node according the prob
void TreeNode::expand(std::unordered_map<int, float> prob, TreeNode ** free_nodes)
{
	for (auto it = prob.begin(); it != prob.end(); ++it) {

		TreeNode * node = *free_nodes;
		(*free_nodes)++;
		node->reset(this, it->second);
		children.insert({ it->first, node });
	}
}

void TreeNode::update(int leaf_value)
{
	n_visits++;
	Q += (float) (1.0*(leaf_value - Q) / (float) n_visits);
}

void TreeNode::update_recursive(int leaf_value)
{
	if (parent_p != NULL)
		parent_p->update_recursive(-leaf_value);

	update(leaf_value);
}

float TreeNode::get_value(float c_puct)
{
	u = (float) (c_puct * P * sqrt(parent_p->n_visits)) / (1 + n_visits);
	return Q + u;
}

// select the child with max value, return the action and send p to the child
int TreeNode::select(float c_puct, TreeNode ** p)
{
	if (children.empty())
		return -1;

	auto it = children.begin();
	
	float max_value = it->second->get_value(c_puct);
	int action = it->first;
	*p = it->second;

	for (++it; it != children.end(); ++it) {
		if (it->second->get_value(c_puct) > max_value) {
			max_value = it->second->get_value(c_puct);
			action = it->first;
			*p = it->second;
		}
	}
		
	return action;
}

void TreeNode::release_children()
{
	if (is_leaf()) return;

	for (auto it = children.begin(); it != children.end(); ++it) {
		it->second->release_children();
		delete it->second;
	}
	children.clear();
}

int MCTSPlayer::get_action(Board * board_p) {

	time_t start = time(nullptr);
	
	//Check if is the board full
	auto availables = board_p->get_availables();
	if (availables->size() <= 0)
		return -1;
	
	//Playout, contruct the search tree
	for (auto i = 0; i < n_playout; i++) {
		Board boad_copy = *board_p;  // This should be a deep copy
		//TODO, check deep copy
		playout(&boad_copy); //Every playout will start from the same board, but the Tree will grow
	}

	//Select the best move
	int move = 0;
	float c_puct_action = 0.0; // TODO, adjust this value
	float q = root_p->children.begin()->second->get_value(c_puct_action); 
	for (auto it = root_p->children.begin(); it != root_p->children.end(); ++it) {
		if (it->second->get_value(c_puct_action) > q) {
			move = it->first;
			q = it->second->get_value(c_puct_action);
		}
	}

	//Reset the search tree for next action
	reset_mct();
	std::cout << "Time cost:" << time(nullptr) - start << std::endl;

	return move;
}

void MCTSPlayer::playout(Board * board_p)
{
	TreeNode * p = root_p;
	while (true) {
		if (p->is_leaf()) 
			break;
		auto action = p->select(c_puct, &p);
		board_p->do_move(action);
	}

	if (board_p->get_winner() == PLAYER::NONE) {
		auto prob = explore_policy(board_p);
		p->expand(prob, &free_nodes);
	}
	
	// Update the value of the Tree, this will impact the action for next rollout
	int value = evaluate_rollout(board_p);
	p->update_recursive(-value);
}

int MCTSPlayer::evaluate_rollout(Board * board_p, int limit)
{
	PLAYER player = board_p->get_current_player();
	PLAYER winner = PLAYER::NONE;

	for (auto i = 0; i < limit; i++) {
		winner = board_p->get_winner();

		if (winner != PLAYER::NONE) 
			break;

		// evaluate according the evaluate policy
		auto prob = evaluate_policy(board_p);
		
		// pick up the action with max prob
		int move = -1;
		float max_prob = 0.0;
		for (auto it = prob.begin(); it != prob.end(); ++it) {
			if (it->second > max_prob) {
				max_prob = it->second;
				move = it->first;
			}
		}

		// do the move
		board_p->do_move(move);
	}

	// no winner
	if (winner == PLAYER::BOTH || winner == PLAYER::NONE)
		return 0;

	return winner == player ? 1 : -1;
}

void MCTSPlayer::reset_mct()
{
	root_p = free_nodes = node_pool;
	root_p->reset(nullptr, 1.0);
	free_nodes++;
}


