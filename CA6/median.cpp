#include "median.hpp"
#include "functions.hpp"
Median_OP::Median_OP(const size_t _id, Node* _parent)
	:Operator(_id, _parent, Median) {}

int Median_OP::evaluate(){
	vector <int> numbers = extract(node_child);
	vector <int> sorted = sorted_number(numbers);
	return sorted[sorted.size() / 2];
}


bool Median_OP::is_valid(){
	return node_child.size() > 0;
}