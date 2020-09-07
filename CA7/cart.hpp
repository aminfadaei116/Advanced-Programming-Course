#ifndef __CART_H__
#define __CART_H__

#include <iostream>
#include <vector>

class Offer;
class User;

class Cart{
public:
	Cart();
	void add_offer_to_cart(float, Offer*, int);
	std::string info();
	float total_cost();
	void submit();
	void increase_sellers_credit(std::vector <User*>);
	std::string sold_info();
	std::string get_buyyer_offer(int);
	std::string cart_info();
protected:
	std::vector <float> costs;
	std::vector <Offer*> carts_offer;
	std::vector <int> amount_offer;
	bool submited;
};

#endif