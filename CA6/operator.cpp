#include "operator.hpp"



Operator::Operator(const size_t _id, Node* _parent, OperatorType _type)
	:Node(_id, _parent), type(_type){}

