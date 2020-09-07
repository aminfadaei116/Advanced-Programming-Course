#include <iostream>
#include "tree.hpp"
#include "node.hpp"
#include "operand.hpp"

Node* find_node(vector <Node*> _nodes, size_t _parent_id){

	for(int i = 0; i < _nodes.size(); i++){
		if(_nodes[i]->is_id(_parent_id)){
			return _nodes[i];
		}
	} 

	return NULL;
}

int find_node_idx(vector <Node*> _nodes, size_t _parent_id){

	for(int i = 0; i < _nodes.size(); i++){
		if(_nodes[i]->is_id(_parent_id)){
			return i;
		}
	}

}

vector <int> extract(vector <Node*> _nodes){
	vector <int> number;
	for(int i = 0; i < _nodes.size(); i++){
		number.push_back(_nodes[i]->evaluate());
	}
	return number;
}

vector <int> sorted_number(vector <int> number){
	int temp;
	for(int i = 0; i < number.size(); i++){
		for(int j = 0; j < number.size() - 1; j++){
			if(number[j] > number[j + 1]){
				temp = number[j + 1];
				number[j + 1] = number[j];
				number[j] = temp;
			}
		}
	}
	return number;
}