#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <vector>
// #include "offer.hpp"

using namespace std;

class Offer;
class Wallet;
class Cart;

enum business { SELLER, BUYER, MANAGER};


class User{
public:
	User(std::string, std::string, std::string, business, int);
	bool is_username(std::string);
	bool is_email(std::string);
	bool is_password(std::string);
	virtual void add_offer_to_user(Offer*) {throw 0;};
	virtual std::string my_offers() {throw 0;};
	std::string get_username() { return username; };
	std::string show_wallet(int);
	int get_id();
	business get_type();
	void charge_user_wallet(float);
	void add_to_users_cart(float, Offer*, int);
	std::string show_last_cart();
	std::string submit_users_cart();
	float user_credit();
	void pay(float);
	void inc_sellers_credit(std::vector <User*>);
	void inc_wallet_credit(float);
	std::string get_users_order(int);
	virtual std::string get_buyyers_offer() { throw 0; };
	virtual void add_to_sold(Cart*) { throw 0; };
protected:
	std::string email;
	std::string username;
	int password;
	business business_type;
	Wallet* users_wallet;
	std::vector <Cart*> carts;
	int id;
};

#endif