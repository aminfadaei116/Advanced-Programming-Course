#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include <iostream>
#include "node.hpp"
#include <vector>

using namespace std;

class Operator: public Node{
public:
	Operator(const size_t, Node*, OperatorType);
	virtual int evaluate() = 0;
protected:
	OperatorType type;
};

#endif