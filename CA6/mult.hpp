#ifndef __MULTI_H__
#define __MULTI_H__

#include <iostream>
#include "operator.hpp"

using namespace std;

class Multiply_OP: public Operator{
public:
	Multiply_OP(const size_t, Node*);
	int evaluate();
	bool is_valid();
protected:
};

#endif