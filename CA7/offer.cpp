#include "offer.hpp"

Offer::Offer(int _offer_id, int _product_id, float _unit_price, int _number_product, std::string _product_name, int _seller_id):
	offer_id(_offer_id), product_id(_product_id), unit_price(_unit_price), number_product(_number_product), product_name(_product_name), seller_id(_seller_id) {}

Offer::Offer() :
	offer_id(0), product_id(0), unit_price(0), number_product(0) {}

int Offer::get_id(){
	return offer_id;
}

int Offer::get_prod_id(){
	return product_id;
}

float Offer::get_price(){
	return unit_price;
}

int Offer::get_number_prod(){
	return number_product;
}

void Offer::change_offer(float _unit_price, int _number_product){
	unit_price = _unit_price;
	number_product = _number_product;
}

string Offer::get_prod_name(){
	return product_name;
}

int Offer::get_seller_id(){
	return seller_id;
}

void Offer::reduce_amount(int _number){
	number_product -= _number;
}