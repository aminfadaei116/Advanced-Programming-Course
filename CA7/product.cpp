#include "product.hpp"
#define OK "OK"
Product::Product(string _name, int _id) : name(_name), id(_id), unit_price(0), number_product(0) {}

string Product::get_name(){
	return name;
}

int Product::get_id(){
	return id;
}

string Product::post_info_product(Offer* current_offer){
	products_offer.push_back(current_offer);
	return OK;
}

string Product::show_offers(){
	string statment = "";
	statment += "productId | productName | offerId | offerUnitPrice | offerAmount\n";
	for(int i = 0; i <products_offer.size(); i++){
		statment += to_string(id);
		statment += " | ";
		statment += name;
		statment += " | ";
		statment += to_string(products_offer[i]->get_id());
		statment += " | ";
		statment += to_string(products_offer[i]->get_price());
		statment += " | ";
		statment += to_string(products_offer[i]->get_number_prod());
		statment += "\n";
	}
	return statment;
}

Product_Type Product::get_type(){
	return type;
}

void Product::add_comment(Comment* _current_comment){
	products_comment.push_back(_current_comment);
}

string Product::show_comments(){
	string statment = "";
	statment += name;
	for(int i = products_comment.size() - 1; i >= 0; i--){
		statment += products_comment[i]->show_comment();
	}
	return statment;
}