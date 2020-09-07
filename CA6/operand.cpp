#include "operand.hpp"

Operand::Operand(const size_t _id, Node* _parent, const int _value)
	:Node(_id, _parent), value(_value){}

int Operand::evaluate(){
	return value;
}

bool Operand::is_operand() {
	return true;
}