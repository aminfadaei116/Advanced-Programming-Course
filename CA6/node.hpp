#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <vector>
#include "node.hpp"

using namespace std;

enum OperatorType { Add, Multiply, Not, Median};

class Node{
public:
	Node(const size_t, Node*);
	Node(const size_t);
	bool is_id(size_t);
	void add_child(Node*);
	virtual int evaluate();
	void print();
	virtual bool is_valid();
	virtual bool is_operand();
	bool is_valid_as_root();
protected:
	int id;
	Node* parent;
	vector <Node*> node_child;
};

#endif