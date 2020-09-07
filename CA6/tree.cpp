#include "tree.hpp"
#include "node.hpp"
#include "functions.hpp"
#include "operand.hpp"
#include "add.hpp"
#include "not.hpp"
#include "mult.hpp"
#include "median.hpp"
#include "exeptions.hpp"
#define DUMMY_ROOT -1

using namespace std;

Tree::Tree(){
	nodes.push_back(new Node(DUMMY_ROOT));
}

void Tree::add_operand_node(const size_t _id, const size_t _parent_id, const int _value){
	check_exist_parent(_parent_id);
	check_existing_id(_id);
	check_is_operator_parent(_parent_id);
	nodes.push_back(new Operand(_id, nodes[find_node_idx(nodes, _parent_id)], _value));
	nodes[find_node_idx(nodes, _parent_id)]->add_child(nodes[find_node_idx(nodes, _id)]);
	if(!nodes[0]->is_valid_as_root())
		throw new Invalid_parent_ex();
}

void Tree::add_operator_node(const size_t _id, const size_t _parent_id, const OperatorType _type){
	check_exist_parent(_parent_id);
	check_existing_id(_id);
	check_is_operator_parent(_parent_id);
	switch(_type){
		case Add:
			nodes.push_back(new Add_OP(_id, nodes[find_node_idx(nodes, _parent_id)]));
			nodes[find_node_idx(nodes, _parent_id)]->add_child(nodes[find_node_idx(nodes, _id)]);
		break;
		case Multiply:
			nodes.push_back(new Multiply_OP(_id, nodes[find_node_idx(nodes, _parent_id)]));	
			nodes[find_node_idx(nodes, _parent_id)]->add_child(nodes[find_node_idx(nodes, _id)]);
		break;
		case Not:
			nodes.push_back(new Not_OP(_id, nodes[find_node_idx(nodes, _parent_id)]));
			nodes[find_node_idx(nodes, _parent_id)]->add_child(nodes[find_node_idx(nodes, _id)]);
		break;
		case Median:
			nodes.push_back(new Median_OP(_id, nodes[find_node_idx(nodes, _parent_id)]));
			nodes[find_node_idx(nodes, _parent_id)]->add_child(nodes[find_node_idx(nodes, _id)]);
		break;
		default:
		return;
	}
	if(!nodes[0]->is_valid_as_root())
		throw new Invalid_parent_ex();
}

bool Tree::is_valid() {
	for(int i = 0; i<nodes.size(); i++)
		if(!nodes[i]->is_valid())
			return false;
	return true;
}

int Tree::evaluate_tree() {
	if(!this->is_valid())
		throw new Invalid_ex();
	return nodes[0]->evaluate();
}

void Tree::check_exist_parent(int _id){
	int flag = 0;
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->is_id(_id))
			flag = 1;
	}
	if(flag == 0)
		throw new NotExist_Parent_ex();
}

void Tree::check_existing_id(int _id){
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->is_id(_id))
			throw new Duplicate_ID_ex();
	}
}

void Tree::check_is_operator_parent(int _id){
	if(nodes[find_node_idx(nodes, _id)]->is_operand())
		throw new Invalid_parent_ex();
}