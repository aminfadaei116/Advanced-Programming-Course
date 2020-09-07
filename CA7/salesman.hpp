#ifndef __SALESMAN_H__
#define __SALESMAN_H__

#include <iostream>
#include <vector>
#include "user.hpp"
#include "offer.hpp"


class Salesman: public User{
public:
	Salesman(std::string _email, std::string _username, std::string _password, int);
	void add_offer_to_user(Offer*);
	std::string my_offers();
	void sort_offers();
protected:
	std::vector <Offer*> salesman_offers;
};

#endif