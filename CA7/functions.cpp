#include "functions.hpp"
#include <iostream>
#include <bits/stdc++.h> 

#include "product.hpp"
#include "offer.hpp"
#include "mobile.hpp"
#include "car.hpp"
#include "tv.hpp"
#include "exeption.hpp"

#define POST_TXT "POST"
#define GET_TXT "GET"
#define SIGNUP_TXT "signup"
#define LOGIN_TXT "login"
#define LOGOUT_TXT "logout"
#define IMPORT_PRODUCTS_TXT "importProducts"
#define GET_OFFERS_TXT "offers"
#define GET_PRODUCTS_TXT "getProducts"
#define POST_OFFER_TXT "offer"
#define QUESTION_MARK "?"
#define GET_MYOFFERS_TXT "myOffers"
#define POST_CHANGE_OFFER_TXT "changeOffer"
#define GET_WALLET_TXT "wallet"
#define POST_GENERATE_DISCOUNT_CODE_TXT "generateDiscountCode"
#define GET_OFFERS_ON_PRODUCT_TXT "offersOnProduct"
#define GET_PRODUCT_DETAIL_TXT "productDetail"
#define GET_COMMENTS_TXT "comments"
#define POST_ADD_TO_CART_TXT "addToCart"
#define GET_CART_TXT "cart"
#define POST_SUBMIT_CART_TXT "submitCart"
#define GET_ORDERS_TXT "orders"
#define POST_CHARGE_WALLET_TXT "chargeWallet"
#define POST_COMMENT_TXT "comment"
#define GET_COMPARE_TXT "compare"
#define GET_OFFER_BUYERS_TXT "offerBuyers"
#define CAR_TXT "car"
#define TV_TXT "tv"
#define MOBILE_TXT "mobile"
#define SELLER_TXT "seller"
#define BUYYER_TXT "buyyer"
#define MANAGER_TXT "manager"
#define ONE "1"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define FILEPATH "filePath"
#define TYPE "type"
#define ORDER "order"
#define FIELD "field"
#define PRODUCT_ID "productId"
#define OFFER_UNIT "offerUnitPrice"
#define OFFER_AM "offerAmount"
#define COUNT "count"
#define OFFER_ID "offerId"
#define DISCOUNT_PER "discountPercent"
#define DISCOUNT_NUM "discountNumber"
#define AMOUNT "amount"
#define DISCOUNT_CODE "discountCode"
#define COMMENT "comment"
#define PRODUCT_ID1 "productId1"
#define PRODUCT_ID2 "productId2"
#define EVAL_TXT "evaluateModel"

using namespace std;

string_vector remove_dup_word(string str){ 
	vector <string> words;
    istringstream ss(str); 
    do { 
        string word; 
        ss >> word;  
        words.push_back(word);
    } while (ss);
    words.pop_back(); 
    return words;
}

Command_Type config_command(vector <string> command){
	if((command.size() == 9 || command.size() == 11) && command[0] == POST_TXT && command[2] == QUESTION_MARK && command[1] == SIGNUP_TXT && command[3] == EMAIL && command[5] == USERNAME && command[7] == PASSWORD){
		return SIGNUP;
	}
	else if(command.size() == 7 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == LOGIN_TXT && command[3] == EMAIL && command[5] == PASSWORD){
		return LOGIN;
	}
	else if(command.size() == 2 && command[0] == POST_TXT && command[1] == LOGOUT_TXT)
		return LOGOUT;
	else if(command.size() == 7 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == IMPORT_PRODUCTS_TXT && command[3] == TYPE && command[5] == FILEPATH)
		return IMPORT_PRODUCTS;
	else if(command.size() == 7 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_OFFERS_TXT && command[3] == ORDER && command[5] == FIELD)
		return GET_OFFERS;
	else if(command.size() == 2 && command[0] == GET_TXT && command[1] == GET_PRODUCTS_TXT)
		return GET_PRODUCTS;
	else if(command.size() == 9 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == POST_OFFER_TXT && command[3] == PRODUCT_ID && command[5] == OFFER_UNIT && command[7] == OFFER_AM)
		return POST_OFFER;
	else if(command.size() == 2 && command[0] == GET_TXT && command[1] == GET_MYOFFERS_TXT)
		return GET_MYOFFERS;
	else if(command.size() == 9 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == POST_CHANGE_OFFER_TXT && command[3] == PRODUCT_ID && command[5] == OFFER_UNIT && command[7] == OFFER_AM)
		return POST_CHANGE_OFFER;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_WALLET_TXT && command[3] == COUNT)
		return GET_WALLET;
	else if(command.size() == 9 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == POST_GENERATE_DISCOUNT_CODE_TXT && command[3] == OFFER_ID && command[5] == DISCOUNT_PER && command[7] == DISCOUNT_NUM)
		return POST_GENERATE_DISCOUNT_CODE;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_OFFERS_ON_PRODUCT_TXT && command[3] == PRODUCT_ID)
		return GET_OFFERS_ON_PRODUCT;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_PRODUCT_DETAIL_TXT && command[3] == PRODUCT_ID)
		return GET_PRODUCT_DETAIL;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_COMMENTS_TXT && command[3] == PRODUCT_ID)
		return GET_COMMENTS;
	else if((command.size() == 7 || (command.size() == 9 && command[7] == DISCOUNT_CODE)) && command[2] == QUESTION_MARK &&  command[0] == POST_TXT && command[1] == POST_ADD_TO_CART_TXT && command[3] == OFFER_ID && command[5] == AMOUNT)
		return POST_ADD_TO_CART;
	else if(command.size() == 2 && command[0] == GET_TXT && command[1] == GET_CART_TXT)
		return GET_CART;
	else if(command.size() && command[0] == POST_TXT && command[1] == POST_SUBMIT_CART_TXT)
		return POST_SUBMIT_CART;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_ORDERS_TXT && command[3] == COUNT)
		return GET_ORDERS;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == POST_CHARGE_WALLET_TXT && command[3] == AMOUNT)
		return POST_CHARGE_WALLET;
	else if(command.size() >= 7 && command[2] == QUESTION_MARK && command[0] == POST_TXT && command[1] == POST_COMMENT_TXT && command[3] == PRODUCT_ID && command[5] == COMMENT)
		return POST_COMMENT;
	else if(command.size() == 5 && command[2] == QUESTION_MARK && command[0] == GET_TXT && command[1] == GET_COMPARE_TXT && command[3] == PRODUCT_ID1 && command[5] == PRODUCT_ID2)
		return GET_COMPARE;
	else if(command.size() == 2 && command[0] == GET_TXT && command[1] == GET_OFFER_BUYERS_TXT)
		return GET_OFFER_BUYERS;
	else if(command.size() == 2 && command[0] == POST_TXT && command[1] == EVAL_TXT)
		return POST_EVALUATE;
	else
		return IDK;
}

bool does_username_exist(vector <User*> _users, string _username){
	for(int i = 0; i < _users.size(); i++){
		if(_users[i]->is_username(_username))
			return true;
	}
	return false;
}

bool does_email_exist(vector <User*> _users, string _email){
	for(int i = 0; i < _users.size(); i++){
		if(_users[i]->is_email(_email))
			return true;
	}
	return false;	
}

business config_status(string _status){
	if(_status == SELLER_TXT)
		return SELLER;
	else if(_status == BUYYER_TXT)
		return BUYER;
	else if(_status == MANAGER_TXT)
		return MANAGER;
}

int find_user_idx(vector <User*> _users, string _email){
	for(int i = 0; i < _users.size(); i++){
		if(_users[i]->is_email(_email))
			return i;
	}
	return -1;
}

Product_Type config_product(string product_name){
	if(product_name == CAR_TXT)
		return CAR;
	else if(product_name == TV_TXT)
		return TV;
	else if(product_name == MOBILE_TXT)
		return MOBILE;
}

string_vector get_title_car(ifstream & file){
	string_vector title;
	string input;
	for(int i = 0; i < 5; i++){
		getline(file, input, ',');
		title.push_back(input);
	}
	getline(file, input, '\n');
	title.push_back(input);
	return title;
}

string_vector get_title_mobile(ifstream & file){
	string_vector title;
	string input;
	for(int i = 0; i < 7; i++){
		getline(file, input, ',');
		title.push_back(input);
	}
	getline(file, input, '\n');
	title.push_back(input);
	return title;
}

string_vector get_title_tv(ifstream & file){
	string_vector title;
	string input;
	for(int i = 0; i < 5; i++){
		getline(file, input, ',');
		title.push_back(input);
	}
	getline(file, input, '\n');
	title.push_back(input);
	return title;
}

Car* get_file_car(ifstream & file, int _id){
	string name, weight, num_seats, num_cylinder, engine_capacity, reverse_sensor;
	getline(file, name, ',');
	getline(file, weight, ',');
	getline(file, num_seats, ',');
	getline(file, num_cylinder, ',');
	getline(file, engine_capacity, ',');
	getline(file, reverse_sensor, '\n');
	return new Car(name, string_to_float(weight), string_to_int(num_seats), string_to_int(num_cylinder), string_to_float(engine_capacity), string_to_bool(reverse_sensor), _id);
}

Mobile* get_file_mobile(ifstream & file, int _id){
	string name, weight, frequency, memory, RAM, disp_size, disp_resolution, OS;
	getline(file, name, ',');
	getline(file, weight, ',');
	getline(file, frequency, ',');
	getline(file, memory, ',');
	getline(file, RAM, ',');
	getline(file, disp_size, ',');
	getline(file, disp_resolution, ',');
	getline(file, OS, '\n');
	return new Mobile(name, string_to_float(weight), string_to_float(frequency), string_to_int(memory), string_to_int(RAM), string_to_float(disp_size), string_to_float(disp_resolution), OS, _id);
}

Tv* get_file_tv(ifstream & file, int _id){
	string name, screen_size, screen_type, resolution, is_3d, is_HDR;
	getline(file, name, ',');
	getline(file, screen_size, ',');
	getline(file, screen_type, ',');
	getline(file, resolution, ',');
	getline(file, is_3d, ',');
	getline(file, is_HDR, '\n');
	return new Tv(name, string_to_float(screen_size), screen_type, resolution, string_to_bool(is_3d), string_to_bool(is_HDR), _id);
}

float string_to_float(string string_number){
	stringstream number(string_number);
	float int_number = 0;
	number >> int_number;
	return int_number;
}

bool string_to_bool(string number){
	return (number == ONE);
}

int string_to_int(string number){
    stringstream geek(number); 
    int x = 0; 
    geek >> x;
    return x;
}

bool does_product_exist(vector <Product*> _products, string _id){
	for(int i = 0; i < _products.size(); i++){
		if(_products[i]->get_id() == string_to_int(_id))
			return true;
	}
	return false;
}

int find_product_idx(vector <Product*> _products, string _id){
	for(int i = 0; i < _products.size(); i++){
		if(_products[i]->get_id() == string_to_int(_id))
			return i;
	}
	return -1;
}

bool does_offer_exist(std::vector <Offer*> offers, std::string id){
	for(int i = 0; i < offers.size(); i++){
		if(offers[i]->get_id() == string_to_int(id))
			return true;
	}
	return false;
}

int find_offer_idx(std::vector <Offer*> offers, std::string id){
	for(int i = 0; i < offers.size(); i++){
		if(offers[i]->get_id() == string_to_int(id))
			return i;
	}
	return -1;
}

string gen_random_str(int length){
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string code = "";
    for(int i = 0; i < length; i++){
    	code += alphanum[rand() % (sizeof(alphanum) - 1)];
    }	
    return code;
}

bool does_discount_exist(vector <Discount*> discounts, string code){
	for(int i = 0; i < discounts.size(); i++){
		if(discounts[i]->get_code() == code)
			return true;
	}
	return false;
}

int find_discount_idx(vector <Discount*> discounts, string code){
	for(int i = 0; i < discounts.size(); i++){
		if(discounts[i]->get_code() == code)
			return i;
	}
	return -1;
}

int find_users_index(vector <User*> users, int _id){
	for(int i = 0; i < users.size(); i++){
		if(users[i]->get_id() == _id)
			return i;
	}
	return -1;
}

void get_header(ifstream & file){
	string temp;
	getline(file, temp, '\n');
}