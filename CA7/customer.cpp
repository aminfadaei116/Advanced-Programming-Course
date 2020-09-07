#include "customer.hpp"
#include "wallet.hpp"

#define HEADER "productId | offerId | buyerId | soldPrice | amount\n"
using namespace std;

Customer::Customer(string _email, string _username, string _password, int _id):
	User(_email, _username, _password, BUYER, _id) {}


string Customer::get_buyyers_offer(){
	string statment = HEADER;
	for(int i = sold_cart.size() - 1; i >= 0; i--){
		statment += sold_cart[i]->get_buyyer_offer(id);
	}
	return statment;
}

void Customer::add_to_sold(Cart* current_cart){
	sold_cart.push_back(current_cart);
}