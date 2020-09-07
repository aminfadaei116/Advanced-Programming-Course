#include "not.hpp"


Not_OP::Not_OP(const size_t _id, Node* _parent)
	:Operator(_id, _parent, Not) {}

int Not_OP::evaluate(){
	return -node_child[0]->evaluate();
}


bool Not_OP::is_valid(){
	return node_child.size() == 1;
}