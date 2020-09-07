#include "salesman.hpp"
#include "offer.hpp"
#include<bits/stdc++.h>
#define MY_OFFER_HEADER "productId | offeredId | offerUnitPrice | offerAmount\n"


Salesman::Salesman(std::string _email, std::string _username, std::string _password, int _id):
	User(_email, _username, _password, SELLER, _id) {}

void Salesman::add_offer_to_user(Offer* current_offer){
	salesman_offers.push_back(current_offer);
}

std::string Salesman::my_offers(){
	sort_offers();
	std::string statment ="";
	statment += MY_OFFER_HEADER;
	for(int i = 0; i < salesman_offers.size(); i++){
		statment += to_string(salesman_offers[i]->get_prod_id());
		statment += " | ";
		statment += to_string(salesman_offers[i]->get_id());
		statment += " | ";
		statment += to_string(salesman_offers[i]->get_price());
		statment += " | ";
		statment += to_string(salesman_offers[i]->get_number_prod());
		statment += "\n";
	}
	return statment;
}

void Salesman::sort_offers(){
	for(int i = 0; i < salesman_offers.size(); i++){
		for(int j = 0; j < salesman_offers.size() - 1; j++){
			if(salesman_offers[j]->get_id() > salesman_offers[j + 1]->get_id()){
				swap(salesman_offers[j], salesman_offers[j + 1]);
			}
		}
	}
}
