#include "add.hpp"


Add_OP::Add_OP(const size_t _id, Node* _parent)
	:Operator(_id, _parent, Add) {}

int Add_OP::evaluate(){
	int sum = 0;
	for(int i = 0; i < node_child.size(); i++){
		sum += node_child[i]->evaluate();
	}
	return sum;
}


bool Add_OP::is_valid(){
	return node_child.size() == 2;
}