#ifndef __OPERAND_H__
#define __OPERAND_H__

using namespace std;
#include "node.hpp"

class Operand: public Node{
public:
	Operand(const size_t, Node*, const int);
	int evaluate();
	bool is_operand();
protected:
	int value;

};

#endif