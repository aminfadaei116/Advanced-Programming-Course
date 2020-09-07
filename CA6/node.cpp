#include "node.hpp"
#include <vector>
#include "tree.hpp"
#include "node.hpp"
#include "functions.hpp"
#include "operand.hpp"
#include "add.hpp"
#include "not.hpp"
#include "mult.hpp"
#include "median.hpp"

#define DUMMY_ROOT -1

using namespace std;

Node::Node(const size_t _id):
	id(_id){}

Node::Node(const size_t _id, Node* _parent):
	id(_id), parent(_parent){}

bool Node::is_id(size_t _id){
	return (id == _id);
}

void Node::add_child(Node* _child){
	node_child.push_back( _child);
}

int Node::evaluate(){
	return node_child[0]->evaluate();
}

bool Node::is_valid(){
	return true;
}

bool Node::is_operand() {
	return false;
}

bool Node::is_valid_as_root() {
	return node_child.size() <= 1;
}