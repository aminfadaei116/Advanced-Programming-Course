#include "mult.hpp"


Multiply_OP::Multiply_OP(const size_t _id, Node* _parent)
	:Operator(_id, _parent, Multiply) {}

int Multiply_OP::evaluate(){
	int result = 1;
	for(int i = 0; i < node_child.size(); i++){
		result *= node_child[i]->evaluate();
	}
	return result;
}


bool Multiply_OP::is_valid(){
	return node_child.size() == 2;
}