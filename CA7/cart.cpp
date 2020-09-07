#include "cart.hpp"
#include "offer.hpp"

#define HEADER_BUYYER "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount\n"
#define HEADER_SELLER "productId | productName | offerId | sellerId | soldPrice | amount\n"
#define UNSUBMITTED 0
#define SUBMITTED 1
using namespace std;

Cart::Cart(){
	submited = UNSUBMITTED;
}

void Cart::add_offer_to_cart(float _cost, Offer* _current_offer, int _amount){
	costs.push_back(_cost);
	carts_offer.push_back(_current_offer);
	amount_offer.push_back(_amount);
}

string Cart::info(){
	string statment = HEADER_BUYYER;
	statment += cart_info();
	return statment;
}

string Cart::sold_info(){
	string statment = HEADER_SELLER;
	statment += cart_info();
	return statment;
}

string Cart::cart_info(){
	string statment = "";
	for(int i = costs.size() - 1; i >= 0; i--){
		statment += to_string(carts_offer[i]->get_prod_id());
		statment += " | ";
		statment += carts_offer[i]->get_prod_name();
		statment += " | ";
		statment += to_string(carts_offer[i]->get_seller_id());
		statment += " | ";
		statment += to_string(costs[i]);
		statment += " | ";
		statment += to_string(amount_offer[i]);
		statment += "\n";
	}
	return statment;
}

float Cart::total_cost(){
	float total = 0;
	for(int i = 0; i < costs.size(); i++){
		total += costs[i];
	}
	return total;
}

void Cart::submit(){
	bool submited = SUBMITTED;
	for(int i = 0; i < carts_offer.size(); i++){
		carts_offer[i]->reduce_amount(amount_offer[i]);
	}
}

void Cart::increase_sellers_credit(vector <User*> users){
	for(int i = 0; i < carts_offer.size(); i++){
		users[find_users_index(users, carts_offer[i]->get_seller_id())]->inc_wallet_credit(costs[i]);
	}
}

string Cart::get_buyyer_offer(int user_id){
	string statment = "";
	for(int i = 0; i < carts_offer.size(); i++){
		statment += to_string(carts_offer[i]->get_prod_id());
		statment += " | ";
		statment += to_string(carts_offer[i]->get_id());
		statment += " | ";
		statment += to_string(user_id);
		statment += " | ";
		statment += to_string(costs[i]);
		statment += " | ";
		statment += to_string(amount_offer[i]);
		statment += "\n";
	}
	return statment;
}