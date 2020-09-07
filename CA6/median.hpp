#ifndef __MEDIAN_H__
#define __MEDIAN_H__

#include <iostream>
#include "operator.hpp"

using namespace std;

class Median_OP: public Operator{
public:
	Median_OP(const size_t, Node*);
	int evaluate();
	bool is_valid();
protected:
};

#endif