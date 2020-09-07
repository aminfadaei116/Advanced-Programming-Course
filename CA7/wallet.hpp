#ifndef __WALLET_H__
#define __WALLET_H__

#include <iostream>
#include <vector>
#include "functions.hpp"


class Wallet{
public:
	Wallet();
	void add_credit(float);
	std::string show_credit(int);
	float get_credit();
	void reduce_credit(float);
	void inc_credit(float);
	void dec_credit(float);
protected:
	std::vector <float> credits;
	float amount_money;
};

#endif