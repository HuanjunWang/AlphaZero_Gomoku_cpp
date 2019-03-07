#pragma once

#include <unordered_map>
#include<memory>
#include "Player.h"
#include <string>

typedef std::unordered_map<int, float>(*policy_fun)(Board* board_p);


class TreeNode {
private:
	TreeNode* parent_p;
	int n_visits;
	float Q;
	float u;
	float P;
public:
	std::unordered_map<int, TreeNode*> children;

public:
	TreeNode() :parent_p(NULL), n_visits(0), Q(0.0), u(0.0), P(0.0) {}
	TreeNode(TreeNode* parent_p, float prob) :parent_p(parent_p), n_visits(0), Q(0.0), u(0.0), P(prob) {}

	bool is_root();
	bool is_leaf();

	void reset(TreeNode* p_p, float prob) { parent_p = p_p; n_visits = 0; Q = 0.0; u = 0.0; P = prob; children.clear();}
	void expand(std::unordered_map<int, float> prob, TreeNode ** free_nodes);
	void update(int leaf_value);
	void update_recursive(int leaf_value);
	float get_value(float c_puct);
	int select(float c_puct, TreeNode ** p);

	void release_children();

};




class MCTSPlayer :public Player {

private:
	TreeNode * root_p;
	TreeNode * node_pool;
	TreeNode * free_nodes;
	float c_puct;
	int n_playout;

	void playout(Board* board_p);
	int evaluate_rollout(Board* board_p, int limit = 1000);
	void reset_mct();


	policy_fun evaluate_policy;
	policy_fun explore_policy;

public:
	MCTSPlayer(std::string name, int n_playout, float c_puct , policy_fun evaluate, policy_fun rollout) :
		Player(name), 
		n_playout(n_playout),
		c_puct(c_puct),
		evaluate_policy(evaluate), 
		explore_policy(rollout) { 
		
		node_pool = new TreeNode[n_playout*36]; 
		root_p = free_nodes = node_pool;
		free_nodes++;
		root_p->reset(nullptr, 1.0);	
	}
	~MCTSPlayer() { delete [] node_pool; }
	int get_action(Board * board_p);
};



