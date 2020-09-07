#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include <iostream>
#include <vector>
#include "user.hpp"
#include "cart.hpp"
class Customer: public User{
public:
	Customer(std::string _email, std::string _username, std::string _password, int);
	std::string get_buyyers_offer();
	void add_to_sold(Cart*);
protected:
	std::vector <Cart*> sold_cart;
};

#endif