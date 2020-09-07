#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <iostream>
#include <vector>
#include "market.hpp"

using namespace std;



class Interface{
public:
	Interface();
	void processing();

protected:
	Market* friday_market;
};

#endif