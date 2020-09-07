#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <vector>
#include "node.hpp"

#define DUMMY_ROOT -1
#define FAIL 0

class Tree{
public:
	Tree();
	void add_operand_node(const std::size_t id, const std::size_t parent_id, const int value);
    void add_operator_node(const std::size_t id, const std::size_t parent_id, const OperatorType type);
    int evaluate_tree();
    void check_exist_parent(int);
    void check_existing_id(int);
    void check_is_operator_parent(int);
protected:
    bool is_valid();
	vector <Node*> nodes;
};

#endif
