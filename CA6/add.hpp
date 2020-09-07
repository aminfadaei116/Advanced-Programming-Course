#ifndef __ADD_H__
#define __ADD_H__

#include <iostream>
#include "operator.hpp"

using namespace std;

class Add_OP: public Operator{
public:
	Add_OP(const size_t, Node*);
	int evaluate();
	bool is_valid();
protected:
};

#endif