#include "user.hpp"
#include "wallet.hpp"
#include <functional>
#include <string>
#include "cart.hpp"
#include "offer.hpp"
#include <algorithm>
#include "exeption.hpp"

#define EMPTY "Empty"
#define OK "OK"
// template <class T> struct hash;

using namespace std;

hash<string> str_hash;

User::User(string _email, string _username, string _password, business _type, int _id){
	email = _email;
	username = _username;
	password = str_hash(_password);
	business_type = _type;
	id = _id;
	users_wallet = new Wallet();
}

bool User::is_username(string _username){
	return (_username == username);
}

bool User::is_email(string _email){
	return (_email == email);
}

bool User::is_password(string _password){
	int input = str_hash(_password);
	return (password == input);
}

string User::show_wallet(int _count){
	return users_wallet->show_credit(_count);
}

business User::get_type(){
	return business_type;
}

void User::add_to_users_cart(float _cost, Offer* _current_offer, int _amount){
	if(carts.size() == 0)
		carts.push_back(new Cart());
	(carts.back())->add_offer_to_cart(_cost, _current_offer, _amount);
}

string User::show_last_cart(){
	if(carts.size() == 0)
		return EMPTY;
	return (carts.back())->info();
}

int User::get_id(){
	return id;
}

float User::user_credit(){
	return users_wallet->get_credit();
}

string User::submit_users_cart(){
	if((carts.back())->total_cost() > user_credit()){
		throw new BAD_REQUEST();
	}
	add_to_sold(carts.back());
	(carts.back()->submit());
	pay((carts.back())->total_cost());
	return OK;
}

void User::charge_user_wallet(float _amount_charge){
	users_wallet->add_credit(_amount_charge);
}

void User::pay(float _total_cost){
	users_wallet->dec_credit(_total_cost);
	users_wallet->reduce_credit(_total_cost);
}

void User::inc_sellers_credit(vector <User*> users){
	(carts.back())->increase_sellers_credit(users);
}

void User::inc_wallet_credit(float _credit){
	users_wallet->add_credit(_credit);
	users_wallet->inc_credit(_credit);
}

string User::get_users_order(int _count){
	int count = 0;
	if(_count > carts.size())
		count = carts.size();
	else
		count = _count;
	string statment = "";
	for(int i = carts.size() - 1; i >= carts.size() -count; i--){
		statment += carts[i]->sold_info();
		if(i != carts.size() - count)
			statment += "****\n";
	}
	return statment;
}
