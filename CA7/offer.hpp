#ifndef __OFFER_H__
#define __OFFER_H__

#include <iostream>
#include <vector>
#include "functions.hpp"

class Offer{
public:
	Offer(int, int, float, int, std::string, int);
	Offer();
	void change_offer(float, int);
	int get_id();
	int get_prod_id();
	float get_price();
	int get_number_prod();
	std::string get_prod_name();
	int get_seller_id();
	void reduce_amount(int);
protected:
	int offer_id;
	int product_id;
	float unit_price;
	int number_product;
	std::string product_name;
	int seller_id;
};

#endif