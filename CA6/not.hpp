#ifndef __NOT_H__
#define __NOT_H__

#include <iostream>
#include "operator.hpp"

using namespace std;

class Not_OP: public Operator{
public:
	Not_OP(const size_t, Node*);
	int evaluate();
	bool is_valid();
private:
};

#endif